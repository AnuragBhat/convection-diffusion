#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
	int i;
	char c;
	time_t btime;
	
	flag:
	srand(time(0));
	
	for (i=1;i<=5;i++){
		cout << rand() << " ";
	}
	cout <<"\n";
	
	cout << "Do you wish to run the program again?" << endl;
	cin >> c;
	
	if ((c == 'y')||(c == 'Y')){
		goto flag;
	}
	
	btime = time(0);
	cout << " Seconds passed since 00:00:00 Jan 1st, 1970 : " << btime << endl;
	
	tm *local = localtime(&btime);
	cout << "Local current time is : " << local->tm_hour <<":"<< local->tm_min <<":"<< local->tm_sec << endl;
	
	
	
	return 0;
}