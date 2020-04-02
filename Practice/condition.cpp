#include<iostream>
#include<string>
using namespace std;

int main(){
	int y,b;
	string str;
	
	cout <<"Enter a number greater than 6 \n";
	cin >> y;
	
	b = (y == 0)?1:y;
	
	str = (b>6)?"Correct":"Incorrect";
	
	cout << "\nThe number you entered is :" << str << endl;
	cout << "The value of b and y are: " << b << " and " << y << endl;
	
	return 0;
}