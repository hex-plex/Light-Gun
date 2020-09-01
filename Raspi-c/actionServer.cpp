#include <iostream>
#include <wiringPi.h>

using namespace std;
int ctr = 0;
int flag = 0;
unsigned int prevTime  = millis();
vector< void (*)(void) > callbacks;
void switchDown(void);
int setupSwitch(vector<void (*)(void)> &cal){
    wiringPiSetup();
    callbacks = cal;
    pinMode(1, INPUT);
    wiringPiISR(1,INT_EDGE_BOTH,switchDown);
    while(1){
        delay(1000);
    }
    return 0;
}
void switchDown(void){
    if(flag==1&&!digitalRead(1)&&((millis()-prevTime)>50)){
        for(void (*)(void) item : callbacks ){
            item();
        }
        flag=0;ctr++;prevTime = millis();
    } else if(flag==0&&digitalRead(1)&&(millis()-prevTime > 50)){
        flag=1;prevTime = millis();
    }
}
