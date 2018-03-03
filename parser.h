/// \file parser.h
/// \brief markdown parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-02

#ifndef __PARSER_H
#define __PARSER_H

#include<string>
#include<vector>
#include<regex>

class Markdown {
 public:
  void SetFrontTags();
	void SetBackTags();
  int IsTitle(std::string & s);
  void SetTitle(int level,std::string& s);
	int IsBlockquotes(std::string & s);
	void SetBlockquotes();
	bool IsUnOrderList(std::string& s);
	void SetUnOrderList();
	bool IsOrderList(std::string& s );
	void SetOrderList();
	std::vector<std::string>& GetContent();

 private:
  std::vector<std::string> v;

};
#endif //__PARSER_H
