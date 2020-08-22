#include <opencv2/opencv.hpp>
#include <iostream>
#include "cameraData.cpp"
#define all(c) c.start(),c.end()
void proj2points(std::vector<cv::Point2d> &image_points){
    PointSet model_set;
    cv::FileStorage fs("refpoints.yaml",cv::FileStorage::READ);
    fs>>model_set;
    std::vector<cv::Point3d> model_points(model_set::to_vector());

}

int main()