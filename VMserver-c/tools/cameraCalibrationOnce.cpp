#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include "cameraData.cpp"

int CHECKERBOARD[2]{5,7};
int main(int argc,char** argv){
    int imgCollection=false;
    std::string path = "./images/";
    if(argc>1){
        if(std::string(argv[1])=="-N"){
            imgCollection=true;
            if(argc>2){
                path=argv[2];
            }
        }
    }

    std::vector<std::vector<cv::Point3f> > objpoints;

    std::vector<std::vector<cv::Point2f> > imgpoints;

    std::vector<cv::Point3f> objp;
    for(int i(0); i<CHECKERBOARD[1];i++){
        for(int j(0); j<CHECKERBOARD[0]; j++)
            objp.push_back(cv::Point3f(j,i,0));
    }
    std::vector<cv::String> images;
    if (imgCollection){
        cv::VideoCapture cap;
        cap.open(2,cv::CAP_ANY);
        if(!cap.isOpened()){
            std::cout<<"Camera couldnt be opened\n";
            return -1;
        }
        cv::Mat image;
        cv::namedWindow("Disp",cv::WINDOW_AUTOSIZE);
        std::cout<<"Press f to pay respect\n";
        for(int o(0);o<20;){
            cap>>image;
            if(image.empty()){
                std::cout<<"No image Returned"<<"\n";
                break;
            }
            cv::imshow("Disp",image);
            if(cv::waitKey(1)==102){
                cv::imwrite(path+"image"+std::to_string(o)+".jpg",image);
                o++;
            }
        }
        cv::destroyWindow("Disp");
        cap.release();
    }
    cv::glob(path+"*.jpg",images);

    cv::Mat frame,gray;

    std::vector<cv::Point2f> corner_pts;
    bool success;
    for (int i(0);i<images.size();i++){
        frame = cv::imread(images[i]);
        cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);

        success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0],CHECKERBOARD[1]),corner_pts,cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE );

        if(success){
            cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.001);

            cv::cornerSubPix(gray,corner_pts,cv::Size(11,11),cv::Size(-1,-1),criteria);

            cv::drawChessboardCorners(frame,cv::Size(CHECKERBOARD[0],CHECKERBOARD[1]),corner_pts,success);
            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);
        }
        cv::imshow("Image",frame);
        cv::waitKey(0);
    }
    cv::destroyAllWindows();
    cv::Mat cameraMatrix,distCoeffs,R,T;

    cv::calibrateCamera(objpoints,imgpoints,cv::Size(gray.rows,gray.cols),cameraMatrix,distCoeffs,R,T);

    std::cout<<"cameraMatrix: "<<cameraMatrix<<"\n";
    std::cout<<"distCoeffs: "<<distCoeffs<<"\n";
    std::cout<<"Rotation vector: "<<R<<"\n";
    std::cout<<"Translation vector: "<<T<<"\n";
    CameraParams data(cameraMatrix,distCoeffs,R,T);
    cv::FileStorage fs("configuredInfo.yaml",cv::FileStorage::WRITE);
    data>>fs;
    fs.release();
    return 0;

}
