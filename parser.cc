/// \file parser.cc
/// \brief parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-03

#include<iostream>
#include<cctype>
#include"parser.h"
Markdown::Markdown():status(NORMAL) {
}
void Markdown::Translate(std::vector<std::string>& md) {
  SetFrontTags();
  for(auto s:md) {
    if(status == NORMAL) {
      //Run(s);
      std::cout<<s<<std::endl;
      std::cout<<IsUnOrderList(s)<<std::endl;
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

    } else if(status == CODE) {

    }

  }
  SetBackTags();
}
void Markdown::Run(std::string& s) {
  int level_title = IsTitle(s);
  if(level_title>0)
    SetTitle(level_title,s);
  int level_block = IsBlockquotes(s);
  if(level_block>0)
    SetBlockquotes(level_block,s);
  int level_unorder_list = IsUnOrderList(s);
  if(level_unorder_list>0) {
    SetUnOrderList(level_unorder_list,s);
    status = UNLIST;
  }
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
  std::string left_tag;
  std::string right_tag;
  while(level>0) {
    left_tag.append("<blockquote>");
    right_tag.append("</blockqupte>");
    level--;
  }
  v.push_back(left_tag);
  v.push_back(s_content);
  v.push_back(right_tag);
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
  //v.push_back(s_list);
  //v.push_back("</li>");

}
