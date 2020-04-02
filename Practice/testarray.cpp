#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int* array(int size);

int main(){
	int *p,n,i;
	system("cls");
	
	cout << "Enter the number of random digits: ";
	cin >> n; cout << endl;	
	
	int arr[n];	
	p = array(n);
	
	for (i=0;i<n;i++){
		arr[i] = *p;
		cout<< "arr["<<i<<"] = " << arr[i] << endl;
		p++;
	}	
	delete []p;
	return 0;
}

int* array(int n){
	
	int i;
	static int *r;
	
	r = new int [n];
	
	srand(time(0));
	
	for (i=0;i<n;i++){
		r[i] = rand();
		cout << "r[" <<i<<"] = " << r[i] << endl;
	}
	
	return r;
	
}