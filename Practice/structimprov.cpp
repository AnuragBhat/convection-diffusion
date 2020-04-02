#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdlib>
using namespace std;
using std::setw;

void print(struct detail *, int n);

struct detail{
	string name;
	int age;
};

int main(){
	int i,n;
	system("cls");
	cout << "Enter the number of entries: "; cin >>n; cout << endl;
	
	struct detail man[n];

	
	for (i=0;i<n;i++){
		cout << "Enter the name of the person: ";
		getchar(); //To avoid get line to take the newline character as input
		getline(cin,man[i].name); cout << endl;
		cout << "Enter the age of the person: ";
		cin >> man[i].age; cout << endl;
		//system("cls");
	}
	print(man,n);

	return 0;
}

void print (struct detail *p, int n){
	
	int i;
	cout <<"Person" << setw(13) << "Age"<< endl << endl;
	for (i=0;i<n;i++){
		cout << setw(7) << (*p).name << setw(13) <<(*p).age << endl;	
		p++;
	}
}