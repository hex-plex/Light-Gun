#include <opencv2/opencv.hpp>
#include "cameraData.cpp"
#include "thresh.cpp"

int cofigPoints(cv::VideoCapture &cap){
    std::cout<<"Please press F to select the frame when camera is parrallel to the display\n";
    cv::Mat image;
    if(!cap.isOpened()){
        std::cout<<"NO Feed from the source\n";
        return -1;
    }
    bool flag=true;
    cv::namedWindow("Display",WINDOW_AUTOSIZE);
    while(true){
        cap>>image;
        if(!image.data()){
            std::cout<<"No image is received from the source\n";
            flag=false;break;
        }
        cv::imshow("Display",image);
        if(cv::waitKey(1)&255==5){
            break;
        }
    }
    if(!flag){return -1;}
    std::vector<cv::Point3d> imgpoints;
    if(thresh(image,imgpoints,true)){
        std::cout<<"Points were detected \n";
    }
    else{std::cout<<"retry with all the points in the frame and with good lighting conditions dont over expose near the points!\n";return -1;}

}
