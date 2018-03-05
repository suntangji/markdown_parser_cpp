/// \file main.cpp
/// \brief main fuction
/// \author suntangji, suntangj2016i@gmail.com
/// \version 1.0
/// \date 2018-02-28

#include<iostream>
#include<fstream>
#include"parser.h"


int main(int argc,char* argv[]) {
  std::vector<std::string> md;
  std::vector<std::string> html;
  const std::string default_input = "test.md";
  const std::string default_output = "test.html";
  std::string input;
  std::string output;
  std::string buff;
  if(argc == 1) {
    input = default_input;
    output = default_output;
  } else if(argc == 2) {
    input = argv[1];
    output = default_output;
  } else if(argc >= 3) {
    input = argv[1];
    output = argv[2];
  }
  std::ifstream in(input);
  if(!in.is_open()) {
    perror("open input file error!");
    return -1;
  }
  while(getline(in,buff)) {
    md.push_back(buff);
  }
	//确保status是NORMAL
	md.push_back("\n");
  ///
  //markdown转换
  ///
  Markdown m;
	m.Translate(md);
  html = m.GetContent();


  std::ofstream out(output);
  if(!out.is_open()) {
    perror("open output file error!");
    return -1;
  }
  for(auto i:html) {
    out<<i<<std::endl;
  }

  return 0;

}
