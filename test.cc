#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
	string s;
	ifstream in("1.md");
	getline(in,s);
	cout<<s<<endl;
	cout<<s.size()<<endl;
	return 0;
}
