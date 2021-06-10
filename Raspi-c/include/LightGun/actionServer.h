#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <vector>
#include <cstring>

#ifdef __arm__
#include <wiringPi.h>
#endif

namespace actionServer{

    int status = 0;
    int ctr = 0;
    int flag = 0;
    
    std::vector< void (*)(void) > callbacks;
    void switchDown(void);
    
    void signal_callback_handler(int signum);
    
#ifdef __arm__
    
    unsigned int prevTrig  = millis();
    unsigned int prevTogl  = millis();
    
    int setupSwitch(std::vector<void (*)(void)> &cal);
    void switchDown(void);
    void shutdown(void);    
    void poweron(void);
    void init(void (*f)(void), std::string baddr, Gun& gun);
    void button_set(void (*f)(int* coor));

#endif

    bool ok(void);
    
    void fetch(void);

}
