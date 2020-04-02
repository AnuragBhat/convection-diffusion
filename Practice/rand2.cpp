#include<iostream>
#include<cstdlib>
using namespace std;

int main(){
	int i,j,n,k;

	system("cls");

	cout << "Enter the number of rows and columns of random variables: " << endl;
	cout << "Number of rows:  ";
	cin >> n;
	cout << endl;
	cout << "Number of columns:  ";
	cin >> k;
	cout << endl;

	for (i=1;i<=n;i++){
		srand(i);
		for (j=1;j<=k;j++){
			cout << rand() << "   ";
		}
		cout << "\n";
	}

	return 0;
}