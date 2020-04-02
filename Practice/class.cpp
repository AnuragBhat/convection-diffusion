#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

class data{
	public:
	string name;
	int age;
	data();
	void getage(int a){
		age = a;
	}
	void getname(string n);
	
	protected:
	double percentage;	
};

data::data(void){
	cout << "The output is getting generated" << endl;
}

class subdata:data{
	public:
	void setpercentage(double p);
	double getpercentage(void);
};

void subdata::setpercentage(double percent){
	percentage = percent;
}

double subdata::getpercentage(void){
	return percentage;
}

void data::getname(string n){
	name = n;
}

int main(){
	data person;
	subdata person2;
	person.getname("Anurag Bhattacharjee");
	person.getage(28);
	person2.setpercentage(73.4);
	cout << person.name << endl << person.age << endl << person2.getpercentage() << endl;
	return 0;
}