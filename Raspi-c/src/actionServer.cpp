#include <unistd.h>
#include <iostream>
#include <wiringPi.h>
#include <cstdlib>
#include <signal.h>
#include <vector>
namespace actionServer{

    void shutdown(void);
    void switchDown(void);
    void poweron(void);
    bool ok(void);
    void fetch(void);
    void signal_callback_handler(int signum);
    int status = 0;
    int ctr = 0;
    int flag = 0;
    unsigned int prevTrig  = millis();
    unsigned int prevTogl  = millis();
    std::vector< void (*)(void) > callbacks;
    void switchDown(void);

    void signal_callback_handler(int signum){
        std::cout<<"Shutting down the server ... .. .\n";
        status = -1;
    }
    
    int setupSwitch(std::vector<void (*)(void)> &cal){
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
    
    void init(void (*f)(void)){
        signal(SIGINT, signal_callback_handler);
    }
    void button_set(void (*f)(int* coor)){
    	return;
    }
    
    bool ok(void){
        if (status==-1)
            return false;
        else
            return true;
    }
    
    void fetch(void){
        return ;
    }

}
