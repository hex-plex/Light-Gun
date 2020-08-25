#include <opencv2/opencv.hpp>
#include <iostream>

struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
};

bool thresh(cv::Mat &img,std::vector<cv::Point3d> &pnts,bool flag){
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(img,contours,hierachy,cv::RETR_TREE,cv::CV_CHAIN_APPROX_SIMPLE,cv::CV_CHAIN_APPROX_NONE);
    for(int i=0;i<contours.size(),i++){}
    return flag;
}
