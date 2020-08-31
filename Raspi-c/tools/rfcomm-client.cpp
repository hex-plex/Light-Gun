#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char** argv){
    struct sockaddr_rc addr = {0};
    int s,status;
    char dest[18]="80:91:33:53:1C:BC";
    s = socket(AF_BLUETOOTH, SOCK_STREAM,BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(dest, &addr.rc_bdaddr);
    status = connect(s , (struct sockaddr*)&addr, sizeof(addr));
    if(status==0){
        status = write(s,"hello!",6);
    }
    if(status<0)perror("uh oh!");
    close(s);
    return 0;
}
