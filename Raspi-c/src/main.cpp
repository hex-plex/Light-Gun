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
	std::cout<<"asdfasdfasdff";
	std::string baddr;
	std::ifstream myfile("../.configDevice");
	if(myfile.is_open()){
		getline(myfile,line);
	}
	else{
		std::cout<<"Bluetooth address config not found read manual to set it up\n";
		return -1;
	}
    
    return 0;
}
