#include <iostream>
#include <chrono>
#include <thread>

int main(){
    std::cout<<"countdown:\n";
    for (int i=10;i>0;--i){
        std::cout<<i<<"\n";
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    std::cout<<"Lift off \n";
    return 0;
}