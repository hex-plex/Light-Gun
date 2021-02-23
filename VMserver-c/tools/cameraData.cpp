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
    std::vector<cv::Point3d> pntrvec = std::vector<cv::Point3d>( 4 , cv::Point3d(0.0f,0.0f,0.0f));
    std::vector<cv::Point2d> cnrvec = std::vector<cv::Point2d>(4 , cv::Point2d( 0.0f, 0.0f));
    PointSet(){};
    PointSet(cv::Point3d a1,cv::Point3d a2,cv::Point3d a3,cv::Point3d a4,cv::Point2d b1,cv::Point2d b2, cv::Point2d b3, cv::Point2d b4) {pntrvec[0]=a1,pntrvec[1]=a2,pntrvec[2]=a3,pntrvec[3]=a4,cnrvec[0]=b1,cnrvec[1]=b2,cnrvec[2]=b3,cnrvec[3]=b4;};
    PointSet(std::vector<cv::Point2d> &a, std::vector<cv::Point3d> &b):pntrvec(b),cnrvec(a){};
};
bool operator>>(const PointSet &a, cv::FileStorage &fs){
    if(fs.isOpened()){
        cv::Mat pntrs(a.pntrvec),cnrs(a.cnrvec);
        fs<<"PNTRS"<<pntrs;
        fs<<"CNRS"<<cnrs;
        return true;
    }
    else
        return false;
}
bool operator>>(cv::FileStorage &fs,PointSet &a){
    if(fs.isOpened()){
        cv::Mat pntrs,cnrs;
        fs["PNTRS"]>>pntrs;
        fs["CNRS"]>>cnrs;
        a.pntrvec = pntrs.clone();
        a.cnrvec = cnrs.clone();
        return true;
    }
    else
        return false;
}
int trialofReadWrite(){
    PointSet a;
    a.pntrvec[2] = cv::Point3d(0.0f,1.0f,0.0f);
    cv::FileStorage fs("configparams.yaml",cv::FileStorage::WRITE);
    a>>fs;
    fs.release();
    PointSet b;
    cv::FileStorage ds("configparams.yaml",cv::FileStorage::READ);
    ds>>b;
    std::cout<<b.pntrvec[2];
    return 0;
}
