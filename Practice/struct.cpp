#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;


void print(struct personnel person);

struct personnel{
	char name[50];
	int age;
	char blood[10];
};

int main(){
	struct personnel man1;
	struct personnel man2;
	struct personnel man3;
	
	strcpy(man1.name, "Anurag Bhattacharjee");
	man1.age = 28;
	strcpy(man1.blood , "B+");
	
	strcpy(man2.name, "Asmita Chakraborty");
	man2.age = 34;
	strcpy(man2.blood ,"B+");
	
	man3.age = 6;
	strcpy(man3.name , "Puturi Chakraborty");
	strcpy(man3.blood, "Unknown");
	
	print(man1);
	print(man2);
	print(man3);
	
	return 0;
}

void print(struct personnel person){
	cout <<"The name of person: " << person.name << endl;
	cout <<"The age of person: " << person.age << endl;
	cout <<"The blood group of person: " << person.blood << endl << endl << endl;
}