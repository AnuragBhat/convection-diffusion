#include<iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
using namespace std;

#define ENTER 10
#define Y 121

float cal(float, float, char);
string type(char);

int main(){
	float a,b,res;
	char c,choice;
	int key;
	string d;
	
    start:
	system("cls");
	
	cout << "\nPlease insert two numbers: "<< endl;
	cin >> a;
	cout <<"\n";
	cin >> b;	
	
	flag:
	cout << "\nPlease insert the operation:\n[+] for addition\n[-] for subtraction\n[*] for multiplication\n[/] for division\n" << endl;
	cin >> c;
	
	if (!(c=='+'||c=='-'||c=='*'||c=='/')){
		cout << "Please select a valid input: "<< endl;
		goto flag;
	}

	d = type(c);
	res = cal(a,b,c);
	
	cout << "The result of " << d << " between " << a << " and " << b << " is: " << res << endl;
	
	cout << "Do you want to perform another operation? Press [Y] to continue or any other key to exit: ";
	//cin >> choice;
	key = getch();
	
	switch(key){
		case Y:
		goto start;
		break;
		default:
		break;
	}
	
	return 0;
}
	
string type(char c){
	
	string str; 
	
	switch(c){
		case '+':
		str = "addition";
		break;
		case '-':
		str = "subtraction";
		break;
		case '*':
		str = "multiplication";
		break;
		case '/':
		str = "division";
		break;
	}
	return str;
}

float cal(float a, float b, char c){
	
	float res;
	
	switch(c){
		case '+':
		res = a+b;
		break;
		case'-':
		res = a-b;
		break;
		case'*':
		res = a*b;
		break;
		case'/':
		res = a/b;
		break;
	}
	
	return res;
}
		
		
		
		
		
		
		
		
		
		