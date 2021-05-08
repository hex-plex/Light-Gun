#include<iostream>

#ifdef __arm__
#include<wiringPi.h>

using namespace std;
unsigned int prevTime = millis();
void shutdown(void);
int main(){
    wiringPiSetup();
    pinMode(4, INPUT);
    digitalWrite(4, LOW);
   // switchinterupt();
    //wiringPiISR(1,INT_EDGE_RISING,switchup);
    wiringPiISR(4,INT_EDGE_RISING,shutdown);
    while(1){
        delay(500);
    }
    return 0;
}
void shutdown(void){
    if((millis()-prevTime)>50 && digitalRead(4)==HIGH){
        prevTime=millis();
        cout<<"Shutting Down ... .. .\n";
    }
}
#else
int main(){
    std::cout<<"No GPIOs detected\n";
    return 0;
}