#include <iostream>
#include <wiringPi.h>

namespace actionServer{

    void shutdown(void);
    bool ok(void);
    void fetch(void);
    int status = 0;
    int ctr = 0;
    int flag = 0;
    unsigned unsigned int prevTrig  = millis();
    unsigned int prevTogl  = millis();
    vector< void (*)(void) > callbacks;
    void switchDown(void);
    int setupSwitch(vector<void (*)(void)> &cal){
        wiringPiSetup();
        callbacks = cal;
        pinMode(1, INPUT);
        pinMode(4, INPUT);
        digitalWrite(4, LOW);
        wiringPiISR(1,INT_EDGE_BOTH, switchDown);
        wiringPiISR(4,INT_EDGE_RISING, shutdown);
        wiringPiISR(4,INT_EDGE_FALLING, poweron);
        while(1){
            delay(10000);
        }
        return 0;
    }
    void switchDown(void){
        if(flag==1&&!digitalRead(1)&&((millis()-prevTrig)>50)){
            for(void (*)(void) item : callbacks ){
                item();
            }
            flag=0;ctr++;prevTrig = millis();
        } else if(flag==0&&digitalRead(1)&&(millis()-prevTrig > 50)){
            flag=1;prevTrig = millis();
        }
    }
    void shutdown(void){
        if((millis()-prevTogl)>50 && digitalRead(4)==HIGH){
            prevTogl = millis();
            std::cout<<"Shutting Down ... .. .\n";
            status = 0;
        }
    }
    void poweron(void){
        if((milli()-prevTogl)>50 && digitalRead(4)==LOW && status==0){
            status=1;
            std::cout<<"Connecting device ... .. .\n";
            prevTogl = millis();
        }
    }

    void init(void (*)(void) f){
        return;
    }
    void button_set(void (*)(void) f){
    	return;
    }
    
    bool ok(void){
        return true;
    }
    
    void fetch(void){
        return ;
    }

}
