#include<iostream>
using namespace std;

static int s_val;
void test(){
	s_val = 1;	
}
int main(){
 	for(int i = 0;i<10;++i)
		s_val = 2017;	
	test();
	cout<<s_val<<endl;
	return 0;
}
