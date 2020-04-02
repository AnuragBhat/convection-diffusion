#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
using std::setw;

int main(){
	int i,n,j=1;
	
	system("cls");
	
	cout << "Enter the length of the array:  ";cin >> n; cout << endl;
	int arr[n];
	
	for (i=0;i<=(n-1);i++){
		if ((j==1)||(j-((j/10)*10)==1)&&(j!=11)){
			cout << "Enter the " << j << "st element of the array: ";
		}
		else if ((j==2)||(j-((j/10)*10)==2)&&(j!=12)){
			cout << "Enter the " << j << "nd element of the array: ";
		}
		else if ((j==3)||(j-((j/10)*10)==3)&&(j!=13)){
			cout << "Enter the " << j << "rd element of the array: ";
		}
		else{
			cout << "Enter the " << j << "th element of the array: ";
		}
		cin >> arr[i];
		cout << endl;
		j++;
	}
	
	cout <<" The array you entered is: " << endl << endl;
	
	cout << "Element" << setw( 13 ) << "Value" << endl;
	for (i=0;i<n;i++){
		cout << setw(7) << i << setw(13) << arr[i] << endl;;
	}

return 0;
}	
	