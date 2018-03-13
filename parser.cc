/// \file parser.cc
/// \brief parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-03

#include<iostream>
#include<cctype>
#include<regex>
#include<stack>
#include"parser.h"

int Markdown::pre_block = 0;
int Markdown::count_of_block = 0;
std::vector<std::string> table_context;
std::vector<std::string> table_head;
size_t code_start = 0;

Markdown::Markdown():status(NORMAL) {
}
void Markdown::Translate(std::vector<std::string>& md) {

  SetFrontTags();
  for(size_t i = 0; i< md.size(); ++i) {
    std::string s = md[i];
    if(status == NORMAL) {
      Run(s);
    } else if(status == UNLIST) {
      int level_unorder_list = IsUnOrderList(s);
      if(level_unorder_list>0)
        SetUnOrderList(level_unorder_list,s);
      else {
        v.push_back("</ul>");
        status = NORMAL;
        Run(s);
      }
    } else if(status == LIST) {
      int level_order_list = IsOrderList(s);
      if(level_order_list>0)
        SetOrderList(level_order_list,s);
      else {
        v.push_back("</ol>");
        status = NORMAL;
        Run(s);
      }

    } else if(status == BLOCK) {
      int level_block = IsBlockquotes(s);
      if(level_block > 0 && level_block <= Markdown::pre_block) {
        SetBlockquotes(level_block,s);
      } else if(level_block > 0 && level_block > Markdown::pre_block) {
        Markdown::count_of_block++;
        Markdown::pre_block = level_block;
        v.push_back("<blockquote>");
        SetBlockquotes(level_block,s);
      } else if(level_block == 0) {
        if(s.size() == 0) {
          while(Markdown::count_of_block > 0) {
            v.push_back("</blockquote>");
            Markdown::count_of_block--;
          }
          Markdown::pre_block = 0;
          status = NORMAL;
        } else if(OnlyText(s) > 0) {
          while(Markdown::count_of_block > 0) {
            v.push_back("</blockquote>");
            Markdown::count_of_block--;
          }
          Markdown::pre_block = 0;
          status = NORMAL;
          Run(s);
        } else {
          v.push_back(s+"<br>");
        }

      }

    } else if(status == CODE) {
      if(IsCode(s)) {

        v.push_back("</pre></code>");
        status = NORMAL;
      } else {
        SetCode(s);
      }
    } else if(status == TABLE_START) {
      if(IsTable(s)) {
        //SetTable
        status = TABLE;
      } else {
        v.push_back(md[i-1]);
        //v.push_back(s);
        i--;
        status = NORMAL;
        table_head.clear() ;
        table_context.clear() ;
      }
    } else if(status == TABLE) {
      if(IsTable(s)) {
        SetTable();
      } else {
        if(table_context.empty()) {
          v.push_back(md[i-2]);
          v.push_back(md[i-1]);
        }
        i--;
        table_head.clear();
        table_context.clear();
        status = NORMAL;
      }
    }
  }
	if(status == CODE){
		//std::cout<<code_start<<std::endl;
		//std::cout<<*(v.begin()+code_start);
		v.erase(v.begin()+code_start);
	}
  SetBackTags();
}
bool Markdown::Run(std::string& s) {
  int level_title = IsTitle(s);
  if(level_title>0) {
    SetTitle(level_title,s);
    return true;
  }
  int level_unorder_list = IsUnOrderList(s);
  if(level_unorder_list>0) {
    SetUnOrderList(level_unorder_list,s);
    status = UNLIST;
    return true;
  }
  int level_order_list = IsOrderList(s);
  if(level_order_list>0) {
    SetOrderList(level_order_list,s);
    status = LIST;
    return true;
  }
  int level_block = IsBlockquotes(s);
  if(level_block>0) {
    SetBlockquotes(level_block,s);
    status = BLOCK;
    return true;
  }
  if(IsCode(s)) {
		code_start = v.size();
    SetCode(s);
    status = CODE;
    return true;
  }
  if(IsTable(s)) {
    status = TABLE_START;
    return true;
  }
  v.push_back(s);
  return false;
}
int Markdown::OnlyText(std::string& s) {
  return IsTitle(s) + IsBlockquotes(s) + IsOrderList(s) + IsUnOrderList(s) + IsUnOrderList(s);
}
bool Markdown::IsCode(std::string& s) {
  std::regex re("^```\\s*[a-zA-Z0-9]*\\s*");
  std::smatch sm;
  std::regex_match(s,sm,re);
  if(sm.size()>0) {
    return true;
  }
  return false;
}
void Markdown::SetCode(std::string& s) {
  if(status == NORMAL) {
    v.push_back("<code><pre>");
  } else
    v.push_back(s);
}
void Markdown::SetToken(std::string& s) {
  std::regex re_lt("<");
  std::regex re_and("&");
  std::regex re_link("\\[(.*)\\]\\((.*)\\)");
  std::regex re_img("!\\[(.*)\\]\\((.*)\\)");
  std::regex re_i("\\*([^\\*]+)\\*");
}
void Markdown::SetFrontTags() {
  v.push_back("<!DOCTYPE html>");
  v.push_back("<html lang=\"en\">");
  v.push_back("<head>");
  v.push_back("<title>Markdown Parser</title>");
  v.push_back("<link href=\"https://cdn.bootcss.com/github-markdown-css/2.10.0/github-markdown.css\" rel=\"stylesheet\">");
  v.push_back("</head>");
  v.push_back("<body class=\"markdown-body\">");
}

void Markdown::SetBackTags() {
  v.push_back("</body>");
  v.push_back("</html>");
}
std::vector<std::string>& Markdown::GetContent() {
  return v;
}
int Markdown::IsTitle(std::string& s) {
  size_t index = 0;
  while(index < s.size() && s[index] == '#') {
    index++;
  }
  if(index > 6||(s[index]!= ' ') )
    index = 0;
  return index;
}
void Markdown::SetTitle(int level,std::string& s) {
  std::string s_level = std::to_string(level);
  std::string s_title = s.substr(level+1);
  std::string html = "<h" + s_level + ">" + s_title + "</h"+s_level+">";
  v.push_back(html);
}
int Markdown::IsBlockquotes(std::string& s) {
  std::regex re("^>+\\s+.*?");
  std::smatch sm;
  std::regex_match(s,sm,re);
  if(sm.size() == 0)
    return 0;
  else {
    int index = 0;
    while(s[index] == '>')
      index++;
    return index;
  }
}
void Markdown::SetBlockquotes(int level,std::string& s) {
  std::string s_content = s.substr(level+1);
  if(status == NORMAL) {
    Markdown::pre_block = level;
    while(level>0) {
      v.push_back("<blockquote>");
      level--;
      Markdown::count_of_block++;
    }
    v.push_back(s_content+"<br>");
  } else if(status == BLOCK) {
    v.push_back(s_content + "<br>");
  }


}
int Markdown::IsUnOrderList(std::string& s) {
  size_t index = 0;
  std::regex re("^\\s*[-+*]{1}\\s+.*");
  std::smatch sm;
  std::regex_match(s,sm,re);
  if(sm.size() == 0)
    return 0;
  while(index<s.size() && s[index]== ' ')
    index++;
  if(index<s.size() && (s[index]= '-'|| s[index] == '+' || s[index] == '*')) {
    index++;
    if(index<s.size()&& s[index] == ' ')
      return index;
  }
  return 0;
}
int Markdown::IsOrderList(std::string& s) {
  std::regex re("^\\s*\\d+\\.\\s.*?");
  std::smatch sm;
  std::regex_match(s,sm,re);
  if(sm.size() == 0)
    return 0;
  size_t index = 0;
  while(s[index] == ' ')
    ++index;
  while(isdigit(s[index]))
    ++index;
  return ++index;
}
void Markdown::SetUnOrderList(int pos,std::string& s) {
  std::string s_list = s.substr(pos+1);
  if(status == NORMAL) {
    v.push_back("<ul>");
  }
  v.push_back("<li>"+s_list+"</li>");
}
void Markdown::SetOrderList(int pos,std::string& s) {
  std::string s_order_list = s.substr(pos+1);
  if(status == NORMAL) {
    v.push_back("<ol>");
  }
  v.push_back("<li>"+ s_order_list+"</li>");
}

bool Markdown::IsTable(std::string& s) {
  if(status == NORMAL || status == TABLE) {
    std::regex re("(.+)\\|(.+)");
    std::smatch sm;
    std::regex_match(s,sm,re);
    if(sm.size()>0) {
      if(status == NORMAL) {
        GetTableContext(table_head,s);
      } else
        GetTableContext(table_context,s);
      return true;
    } else
      return false;
  } else if(status == TABLE_START ) {
    std::regex re("\\:*\\-+\\:*\\|\\:*\\-+\\:*");
    std::smatch sm;
    std::regex_match(s,sm,re);
    if(sm.size()>0)
      return true;
    else
      return false;
  }
  return false;
}
void Markdown::GetTableContext(std::vector<std::string>& table_context,std::string& s) {
  std::string tag = "|";
  size_t pos1 = 0, pos2 = 0;
  pos2 = s.find(tag);
  while(pos2!= std::string::npos) {
    table_context.push_back(s.substr(pos1,pos2-pos1));
    pos1 = pos2 + 1;
    pos2 = s.find(tag,pos1);
  }
  if(pos1!= s.size())
    table_context.push_back(s.substr(pos1));
}
void Markdown::SetTable() {
  v.push_back("<table>");
  v.push_back("<tr>");
  for(auto i:table_head) {
    v.push_back("<th>" + i + "</th>" );
  }
  v.push_back("</tr>");
  v.push_back("<tr>");
  for(auto i:table_context) {
    v.push_back("<td>" + i + "</td>" );
  }
  v.push_back("</tr>");
  v.push_back("</table>");

}
