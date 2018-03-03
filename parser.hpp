/// \file parser.hpp
/// \brief markdown parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-02

#ifndef __PARSER_HPP
#define __PARSER_HPP

#include<string>
#include<vector>
#include<regex>

class Markdown {
 public:
  int IsTitle(std::string& s) {
    int index = 0;
    if (s.empty())
      return 0;
    while (s[index] == '#') {
      index++;
    }
    if (index > 6 || s[index] != ' ')
      index = 0;
    return index;
  }
 private:
  std::vector<std::string> v;

};
#endif //__PARSER_HPP
