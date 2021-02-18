#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "actionServer.cpp"
#include "btServer.cpp"

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
    Gun gun; 
    actionServer::init(pair_socket,baddr,gun);            // This should make all the connections ready
    actionServer::button_set(compute,gun);          // This should make all the interrupts ready
    while(actionServer::ok()){                  // Checks if there is no exit command inputted
        actionServer::fetch();                  // Like a spinlock to complete due tasks.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}

void pair_socket(char* dest, Gun* gun){
    gun = Gun(dest);
    return;
}

void compute(int* mouse_coor){
    return;
}
