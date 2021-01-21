#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "actionServer.cpp"
void pair_socket(void);
void compute(int* mouse_coor);
int main(int argc, char** argv){
	std::string baddr;
	std::ifstream myfile("../.configDevice");  //remove ../ please
	if(myfile.is_open()){
		getline(myfile,baddr);
	}else{
		std::cout<<"Bluetooth address config not found read manual to set it up\n";
		return -1;
    }
    actionServer::init(pair_socket);            // This should make all the connections ready
    actionServer::button_set(compute);          // This should make all the interrupts ready
    while(actionServer::ok()){                  // Checks if there is no exit command inputted
        actionServer::fetch();                  // Like a spinlock to complete due tasks.
    }
    
    return 0;
}

void pair_socket(){
    return;
}

void compute(int* mouse_coor){
    return;
}
