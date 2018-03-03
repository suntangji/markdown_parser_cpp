/// \file parser.cc
/// \brief parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-03

#include"parser.h"

void Markdown::SetFrontTags(){
	v.push_back("<!DOCTYPE html>");
	v.push_back("<html lang=\"en\">");
	v.push_back("<head>");
	v.push_back("<title>Markdown Parser</title>");
	v.push_back("<link href=\"https://cdn.bootcss.com/github-markdown-css/2.10.0/github-markdown.css\" rel=\"stylesheet\">");
	v.push_back("</head>");
	v.push_back("<body class=\"markdown-body\">");
}

void Markdown::SetBackTags(){
	v.push_back("</body>");
	v.push_back("</html>");
}
std::vector<std::string>& Markdown::GetContent(){
	return v;
} 
int Markdown::IsTitle(std::string& s){
	size_t index = 0;
	while(index < s.size() && s[index] == '#'){
		index++;
	}
	if(index > 6||(s[index]!= ' ') )
		index = 0;
	return index;
}
void Markdown::SetTitle(int level,std::string& s){
	std::string s_level = std::to_string(level);
	std::string s_title = s.substr(level+1); 
	std::string html = "<h" + s_level + ">" + s_title + "</h"+s_level+">";
	v.push_back(html);
}
int Markdown::IsBlockquotes(std::string& s){
	std::regex re("^>+\\s+.*?");
	std::smatch sm;
	std::regex_match(s,sm,re);
	if(sm.size() == 0)
		return 0;
	else{
		int index = 0;
		while(s[index] == '>')
			index++;
		return index;
	}
}
