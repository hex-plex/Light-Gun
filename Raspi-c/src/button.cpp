#include<iostream>

using namespace std;

#ifdef __arm__
#include<wiringPi.h>


int ctr = 0;
int flag=0;
unsigned int prevTime = millis();
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
    if(flag==1&&!digitalRead(1)&&((millis()-prevTime)>50)){
        cout<<"Button Pressed"<<ctr<<"\n";
     flag=0;ctr++;prevTime=millis();
	} else if(flag==0&&digitalRead(1)&&(millis()-prevTime>50)){
    	cout<<"Down\n";
    	flag=1;prevTime=millis();
	}
}
#else
int main(){
    cout<<"No GPIOs detected\n";
    return 0;
}
void switchdown(void){
    cout<<"No GPIOs detected\n";
}
#endif