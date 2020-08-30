#include<iostream>
#include<wiringPi.h>

using namespace std;
int count = 0;
int flag=0;
void switchdown(void);
int main(){
    wiringPiSetup();
    pinMode(0,OUTPUT);
    pinMode(1,INPUT);
    wiringPiISR(1,INT_EDGE_BOTH,switchdown);
    while(1){
        delay(500);
    }
    return 0;
}
void switchdown(void){
    if(flag==1&&!digitalRead(1)){
    cout<<"Down\n";
     flag=0;
	} else if(flag==0&&digitalRead(1))
    {	
    	cout<<"Button Pressed \n";
    	flag=1;
	}
}
