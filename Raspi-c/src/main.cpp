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
//#include "actionServer.cpp"
int main(){
	std::string baddr;
	std::ifstream myfile("../.configDevice");  //remove ../ please
	if(myfile.is_open()){
		getline(myfile,baddr);
	}else{
		std::cout<<"Bluetooth address config not found read manual to set it up\n";
		return -1;
    }  
    /*actionServer::init(pair_socket);
    actionServer::button_set(compute);
    while(actionServer::ok()){
        actionServer::fetch();
    }*/
    return 0;
}

void pair_socket(){
    return;
}

void compute(int* mouse_coor){
    return;
}
