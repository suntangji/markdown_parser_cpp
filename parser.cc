/// \file parser.cc
/// \brief parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-03

#include"parser.h"

int Markdown::IsTitle(std::string s){
	size_t index = 0;
	while( s[index] == '#'){
		index++;
	}
//index < s.size() &&
	if(index > 6||(s[index]!= ' ') )
		index = 0;
	return index;
}
