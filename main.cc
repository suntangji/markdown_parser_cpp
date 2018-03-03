/// \file main.cpp
/// \brief main fuction
/// \author suntangji, suntangj2016i@gmail.com
/// \version 1.0
/// \date 2018-02-28

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int main(int argc,char* argv[]) {
    vector<string> md;
    vector<string> html;
    const string default_input = "test.md";
    const string default_output = "test.html";
    string input;
    string output;
    string buff;
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
    ifstream in(input);
    if(!in.is_open()){
        perror("open input file error!");
        return -1;
    }
    while(getline(in,buff)){
        md.push_back(buff);
    }
    /// 
    //markdown转换
    ///
    ofstream out(output);
    if(!out.is_open()){
        perror("open output file error!");
        return -1;
    }
    for(auto i:html){
        out<<i<<endl;
    }
    
    return 0;

}
