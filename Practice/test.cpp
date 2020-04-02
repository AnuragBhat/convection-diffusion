#include<iostream>
#include<cstdlib>
using namespace std;

class data{
	public:

	data();
	void seta(int b);
	int geta(void);
	private:
		int a;
};

data::data(void){
	cout << "This is a test" << endl;
}

void data::seta(int b){
	a = b;
}

data::geta(void){
	return a;
}

int main(){
	data line;
	line.seta(28);
	cout << "the number is: " << line.geta() << endl;
	return 0;
}