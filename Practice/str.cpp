#include<iostream>
#include<cstring>

using namespace std;

int main(){
	int len[2],tot;
	system("cls");
	//string s1 = "Hello";
	//string s2 = "World";
	//string s3 = s1 + " " + s2;
	string s3[2] = {"Hello","World"};
	cout << s3[0]+" "+s3[1] << endl;
	len[0] = s3[0].size();
	len[1] = s3[1].size();
	tot = len[0]+len[1];
	cout << "Size is: " << len[0]+len[1];
	
	return 0;
}