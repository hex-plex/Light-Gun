#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char** argv){
    struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
    char buf[1024]= {0};
    int s,client, bytes_read ;
    socklen_t opt = sizeof(rem_addr);
    s = socket(AF_BLUETOOTH,SOCK_STREAM,BTPROTO_RFCOMM);
    loc_addr.rc_family = AF_BLUETOOTH;
    bdaddr_t tmp ={};
    loc_addr.rc_bdaddr = tmp;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s,(struct sockaddr *)&loc_addr, sizeof(loc_addr));
    listen(s,1);
    client = accept(s,(struct sockaddr *)&rem_addr,&opt);
    ba2str(&rem_addr.rc_bdaddr,buf);
    fprintf(stderr,"accepted connection from %s\n",buf);
    while(true){
        memset(buf,0,sizeof(buf));
        bytes_read = read(client,buf,sizeof(buf));
        if(bytes_read>0){
            if(buf[0]==-1)break;

            printf("received [%s]\n",buf);
        } else {
            break;
        }

    }
    close(client);
    close(s);
    return 0;
}
