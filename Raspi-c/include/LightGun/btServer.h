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
