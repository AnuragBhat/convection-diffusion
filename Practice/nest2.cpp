#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

#define ESC 27

int main(){
	int i,j,n,key;
	char choice;
	bool running = true;	
	system("cls");
	
	flag:
	cout << "Do you want to run the star pattern?" << endl;
	cout << "Press [Y] to run\nPress [N] to not run and exit.\nEnter your choice :";
	cin >> choice;
	
	switch (choice){
		case 'Y':
		case 'y': 
	while (running){
		
	cout << "Enter the number of rows: ";
	cin >> n;
	cout << "\n";
	
	for (i=1;i<=n;i++){
		for (j=1;j<=2*n;j++){
			if (j<=i){
				cout << "* ";
			}
			else if ((j>i)&&(j<=(2*n-i))){
				cout << "  ";
			}
			else {
				cout << "* ";
			}
		}
		cout << "\n";
	}
	cout << "press escape key to exit and any other key to continue" <<endl;
	key = getch();
	if (key == ESC){
		running = false;
		//break;
	}
	else {
		continue;
	}
	}
	break;
	
		case 'N':
		case 'n':
		break;
	
	default:
	cout << "Invalid choice, please choose [Y] or [N]" << endl;
	goto flag;
}

	return 0;
}
//Alternate
/*
int main()
{
int i,j,k,m,n;
string str;
cout << "Enter the number of rows: ";
cin >> n;
cout << "\n";

for (i=1;i<=n;i++){
    
    for(j=1;j<=i;j++){
        cout << "* ";
    }
    m = 2*n-i;
    for(k=1;k<=(m);k++){
      //  if (k<=(m-i)){
      //      cout << "  ";
      //  }
      //  else {
      //  cout << "* ";
      //  }
	  str = (k<=(m-i))?"  ":"* ";
	  cout << str;
	  
    }
    
    cout <<"\n";
    
}
   
   return 0;
}
*/