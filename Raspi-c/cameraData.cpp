#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core/persistence.hpp>
#include <iostream>
#include <stdio.h>
struct CV_EXPORTS CameraParams
{
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    cv::Mat R;
    cv::Mat T;
    CameraParams(){};
    CameraParams(const cv::Mat& cm, const cv::Mat& dc, const cv::Mat& r, const cv::Mat& t):cameraMatrix(cm),distCoeffs(dc),R(r),T(t){};
    CameraParams(const CameraParams& other);
    const CameraParams& operator=(const CameraParams& other);
};
bool operator>>(CameraParams &a, cv::FileStorage &fs){
    if(fs.isOpened()){
        fs << "cameraMatrix" << a.cameraMatrix;
        fs << "distCoeffs" << a.distCoeffs;
        fs << "R" << a.R;
        fs << "T" << a.T;
        return true;
    }
    else
        return false;
}
bool operator>>(cv::FileStorage &fs,CameraParams &a){
    if(fs.isOpened()){
        cv::Mat cm,dc,r,t;
        fs["cameraMatrix"] >> cm;a.cameraMatrix = cm.clone();
        fs["distCoeffs"] >> dc;a.distCoeffs= dc.clone();
        fs["R"] >> r;a.R = r.clone();
        fs["T"] >> t;a.T = t.clone();
        return true;
    }
    else
        return false;
}

int trialWrite(){
    cv::Mat cm = cv::Mat::eye(10, 10, CV_32S);
    cv::Mat dc = cv::Mat::eye(10, 10, CV_32S);
    cv::Mat r = cv::Mat::eye(10, 10, CV_32S);
    cv::Mat t = cv::Mat::eye(10, 10, CV_32S);
    CameraParams asdf(cm,dc,r,t);
    cv::FileStorage fs("trial.yaml",cv::FileStorage::WRITE);
    asdf>>fs;
    fs.release();
    return 0;

}
int trialRead(){
    CameraParams asdf;
    cv::FileStorage fs("trial.yaml",cv::FileStorage::READ);
    fs>>asdf;
    fs.release();
    std::cout<<asdf.cameraMatrix<<"\n"<<asdf.distCoeffs<<"\n"<<asdf.R<<"\n"<<asdf.T<<"\n";
    return 0;

}

struct CV_EXPORTS PointSet {
    cv::Point3d ptr1;
    cv::Point3d ptr2;
    cv::Point3d ptr3;
    cv::Point3d ptr4;
    cv::Point2d cnr1;
    cv::Point2d cnr2;
    cv::Point2d cnr3;
    cv::Point2d cnr4;
    PointSet(){};
    PointSet(cv::Point3d a1):ptr1(a1){};
};