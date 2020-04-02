#include<iostream>
using namespace std;

int main(){
	int choice;
	
	flag:
	//Multiple choice question
	cout << "Enter the correct choice(s) :" << endl;
	cin >> choice;
	
	switch (choice){
		case 1:
		cout << "The choice is wrong" << endl;
		break;		
		// The 2nd, 3rd and 4th are correct choices
		case 2:
		case 3:
		case 4:
		cout << "The choice is right" << endl;
		break;		
		case 5:
		cout << "The choice is wrong" << endl;
		break;		
		default:
		cout << "Wrong input\n";
		goto flag;
	}
	return 0;
}
	