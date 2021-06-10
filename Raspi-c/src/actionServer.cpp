#include <LightGun/actionServer.h>

void actionServer::signal_callback_handler(int signum){
    std::cout<<"Shutting down the server ... .. .\n";
    status = -1;
}

#ifdef __arm__

int actionServer::setupSwitch(std::vector<void (*)(void)> &cal){
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

void actionServer::switchDown(void){
    if(flag==1&&!digitalRead(1)&&((millis()-prevTrig)>50)){
        for(void (*)(void) item : callbacks ){
            item();
        }
        flag=0;ctr++;prevTrig = millis();
    } else if(flag==0&&digitalRead(1)&&(millis()-prevTrig > 50)){
        flag=1;prevTrig = millis();
    }
}

void actionServer::shutdown(void){
    if((millis()-prevTogl)>50 && digitalRead(4)==HIGH){
        prevTogl = millis();
        std::cout<<"Shutting Down ... .. .\n";
        status = 0;
    }
}

void actionServer::poweron(void){
    if((milli()-prevTogl)>50 && digitalRead(4)==LOW && status==0){
        status=1;
        std::cout<<"Connecting device ... .. .\n";
        prevTogl = millis();
    }
}


void actionServer::init(void (*f)(void), std::string baddr, Gun& gun){
    signal(SIGINT, signal_callback_handler);
    char dest[18];
    strcpy(dest, baddr.c_str());
    gun = f(dest);
}

void actionServer::button_set(void (*f)(int* coor)){
    return;
}

#endif

bool actionServer::ok(void){
    if (status==-1)
        return false;
    else
        return true;
}

void actionServer::fetch(void){
    return ;
}