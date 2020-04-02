#include<iostream>
using namespace std;

int main(){
	int i,j,n;
	
	cout <<"Please enter the number of stars in rows and columns" << endl;
	cin >> n;
	
	i=n;
	
	for (int p=1;p<=n;p++){
		for (int q =1;q<=p;q++){
			cout <<"*";
		}
		cout <<"\n";
	}
	
	while (i>=1){
		j=i;
		while(j>=1){
			cout << "*";
			j--;
		}
		cout <<"\n";
		i--;
	}
	
	
	return 0;
}