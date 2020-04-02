#include<iostream>
using namespace std;

extern int a,b,c;
extern float d;
extern double f;

int main(){
	//Defining the variables
	int a=5,b=20;
	int c;
	float d;
	double f;
	
	c = a + b;
	
	cout << "The value of c is: " << c << endl;
	 
	d = 70.0/3.0;
	f = 70.0/3.0;
	cout << "The value of float d is: " << d << endl;
	cout << "The value of double f is : " << f << endl;
	
	return 0;
}