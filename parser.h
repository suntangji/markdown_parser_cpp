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
  int IsTitle(std::string s);
	void SetTitle(int level);

 private:
  //std::vector<std::string> v;

};
#endif //__PARSER_H
