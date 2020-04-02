#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int main(){
	//char a[7] = {'A','n','u','r','a','g'};
	char a[] = "My name is Anurag Bhattacharjee";
	int i,n,num;
	
	system("cls");
	
	n = strlen(a);
	num = n;
	char *ptr[num];
	
	//ptr = a;	
	//ptr =&a[0];
	for (i=0;i<num;i++){
		ptr[i] = &a[i];
		cout << *ptr[i];
		if (*ptr[i]==' '){
			n-=1;
		}
		//ptr++;
	}
	cout << "\n\nSize of char array entered: " << num << endl << endl;
	cout << "The number of letters: " << n;
	return 0;
}
		