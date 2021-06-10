#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <LightGun/cameraData.h>
#include "thresh.cpp"

int configPoints(cv::VideoCapture &cap){
    std::cout<<"Please press F to select the frame when camera is parrallel to the display\n";
    cv::Mat image;
    if(!cap.isOpened()){
        std::cout<<"NO Feed from the source\n";
        return -1;
    }
    bool flag=true;
    cv::namedWindow("Display",cv::WINDOW_AUTOSIZE);
    while(true){
        cap>>image;
        if(!image.data){
            std::cout<<"No image is received from the source\n";
            flag=false;break;
        }
        cv::imshow("Display",image);
        if(cv::waitKey(1)==102){
            break;
        }
    }
    if(!flag){return -1;}
    PointSet rad;
    std::vector<cv::Point2d> imgpoints;
    int res[] ={640,480};
    if(thresh(image,imgpoints,true,res)){
        std::cout<<"Points were detected \n";
        std::cout<<"Select a rectangle which defines the inner part of the display the best\n";
        cv::Rect r = cv::selectROI(image);
        rad.pntrvec.clear();
        for(int i=0;i<imgpoints.size();i++){
            rad.pntrvec.push_back(cv::Point3d(imgpoints.at(i).x,imgpoints.at(i).y,10));
        }
        std::vector<cv::Point2d> selpoints;
        selpoints.push_back(cv::Point2d(r.x,r.y));selpoints.push_back(cv::Point2d(r.x+r.width,r.y));selpoints.push_back(cv::Point2d(r.x,r.y+r.height));selpoints.push_back(cv::Point2d(r.x+r.width,r.y+r.height));
        rad.cnrvec = selpoints;
        cv::FileStorage fs("refpoints.yaml",cv::FileStorage::WRITE);
        rad>>fs;
        fs.release();
        std::cout<<"Completed!!\n";
    }
    else{std::cout<<"retry with all the points in the frame and with good lighting conditions dont over expose near the points!\n";return -1;}
    return 1;
}

int main(){
    cv::VideoCapture cap;
    cap.open(0,cv::CAP_ANY);
    if(!cap.isOpened()){
        std::cout<<"Camera couldnt be opened\n";
        return -1;
    }
    int a = configPoints(cap);
    cap.release();
    return a;
}
