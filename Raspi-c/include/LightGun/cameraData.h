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



struct CV_EXPORTS PointSet {
    std::vector<cv::Point3d> pntrvec = std::vector<cv::Point3d>( 4 , cv::Point3d(0.0f,0.0f,0.0f));
    std::vector<cv::Point2d> cnrvec = std::vector<cv::Point2d>(4 , cv::Point2d( 0.0f, 0.0f));
    PointSet(){};
    PointSet(cv::Point3d a1,cv::Point3d a2,cv::Point3d a3,cv::Point3d a4,cv::Point2d b1,cv::Point2d b2, cv::Point2d b3, cv::Point2d b4) {pntrvec[0]=a1,pntrvec[1]=a2,pntrvec[2]=a3,pntrvec[3]=a4,cnrvec[0]=b1,cnrvec[1]=b2,cnrvec[2]=b3,cnrvec[3]=b4;};
    PointSet(std::vector<cv::Point2d> &a, std::vector<cv::Point3d> &b):pntrvec(b),cnrvec(a){};
};


bool operator>>(CameraParams &a, cv::FileStorage &fs);
bool operator>>(cv::FileStorage &fs,CameraParams &a);
bool operator>>(const PointSet &a, cv::FileStorage &fs);
bool operator>>(cv::FileStorage &fs,PointSet &a);

int trialofReadWrite();

int trialWrite();
int trialRead();
