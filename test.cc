#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main(){
	vector<string> v;
	string s;
	ifstream in("test.md");
	getline(in,s);
	v.push_back(s);
	for(auto i:v){
		cout<<i<<endl;
		cout<<i++<<endl;
	}
	return 0;
}
