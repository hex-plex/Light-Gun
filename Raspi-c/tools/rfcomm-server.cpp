#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char** argv){
    struct sockaddr_rc loc_addr = [0], rem_addr = {0};
    char buf[1024]= {0};
    int s,client = byte_ord ;
    socklen_t opt = sizeof(rem_addr);
    s = socker(AF_BLUETOOTH,SOCK_STEAM,BT_PROTO_ADDR );
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) ;
    bind(s,(struct sockaddr *)&loc_addr, sizeof(loc_addr));
    listen(s,1);
    client = accep(s,(struct sockadd *)&rem_addr,&opt);
    ba2str(&rem_addr,rc_badder,buf);
    fprint(stderr,"accepted connection from %s\n",buff);
    memset(buf,0,sizeof(buf));

    bytes_read = read(client,buf,sizeof(buf));
    if(bytes_read>0){
        printf("received [%s]\n",buf);
    }
    close(client);
    close(s);
    return 0;
}
