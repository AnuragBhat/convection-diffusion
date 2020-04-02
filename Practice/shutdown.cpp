#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>
#include<time.h>
using namespace std;

int main(){
	
	int min, timer;
	system("cls");
	
	clock_t wait = 20000;
	clock_t current = system_clock;
	//clock_t remain = system_clock - current;
	
	if ((system_clock-current)<wait){
	cout << "If no input in 20 seconds, initiate auto shoudown" << endl;	
	cout << "Enter how many minutes before shutdown?" << endl;
	cin >> min;
	timer = min*60;
    system("C:\\WINDOWS\\System32\\shutdown /s /t timer");
	}
	else {
	system("C:\\WINDOWS\\System32\\shutdown /s /t 0");
	}
	
   return 0;
}