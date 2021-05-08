#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

class Gun{
    public:
        Gun();
        Gun(char* dst);
        int send(int x, int y);
        int get_status();
        int stop();
    private:
        char dest[18] = "XX:XX:XX:XX:XX:XX";
        struct sockaddr_rc addr = {0};
        int s, status;
};

Gun::Gun(){
    this->s=-1;
    this->status=-1;
}
Gun::Gun(char* dst){
    strcpy(this->dest,dst);
    this->s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    this->addr.rc_family = AF_BLUETOOTH;
    this->addr.rc_channel = (uint8_t) 1;
    str2ba(this->dest, &this->addr.rc_bdaddr);
    this->status = connect(this->s, (struct sockaddr*)&this->addr, sizeof(addr));
}

Gun::send(int x, int y){
    if(this->get_status()>=0){
        char tempx[5];
        char tempy[5];
        int tx=x,ty=y;
        for(int i=4;i>=0;i--){
            tempx[i] = tx%10 + 48 ; 
            tempy[i] = ty%10 + 48 ;
            tx/=10;
            ty/=10;
        }
        char msg[14];
        std::sprintf(msg, "!%s&%s@", tempx, tempy);
        this->status = write(this->s,msg,13);
        delete tempx,tempy,msg,tx,ty;
    }
}