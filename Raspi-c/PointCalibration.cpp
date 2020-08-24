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
        if(cv::waitKey(1)&255==70){
            break;
        }
    }
    if(!flag){return -1;}
    PointSet rad;
    std::vector<cv::Point3d> imgpoints;
    if(thresh(image,imgpoints,true)){
        std::cout<<"Points were detected \n";
        std::cout<<"Select a rectangle which defines the inner part of the display the best\n";
        cv::Rect r = cv::selectROI(image);
        rad.pntrvec = imgpoints;
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
