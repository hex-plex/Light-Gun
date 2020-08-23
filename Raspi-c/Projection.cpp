#include <opencv2/opencv.hpp>
#include <iostream>
#include "cameraData.cpp"
#define all(c) c.start(),c.end()
void getEulerAngles(Mat &rotCameraMatrix,cv::Vec3d &eulerAngles){
    Mat cameraMatrix, rotMatrix,transVect,rotMatrixX,rotMatrixY,rotMatrixZ;
    double* _r = rotCameraMatrix.ptr<double>();
    double projMatrix[12] = {_r[0],_r[1],_r[2],0,
                             _r[3],_r[4],_r[5],0,
                             _r[6],_r[7],_r[8].0};
    cv::decomposeProjectionMatrix(Mat(3,4,cv::CV_64FC1,projMatrix),
                                    cameraMatrix,
                                    rotMatrix,
                                    transVect,
                                    rotMatrix,
                                    rotMatrixX,
                                    rotMatrixY,
                                    rotMatrixZ.
                                    eulerAngles);
}

void proj2points(std::vector<cv::Point2d> &image_points){
    PointSet model_set;
    cv::FileStorage fs("refpoints.yaml",cv::FileStorage::READ);
    fs>>model_set;
    fs.release();
    std::vector<cv::Point3d> model_points = model_set.pntrvec;
    fs = cv::FileStorage("configuredInfo.yaml",cv::FileStorage::READ);
    CameraParams cam_0;
    fs>>cam_0;
    fs.release();
    cv::Mat rotation_vector,translation_vector,rotation_matrix;
    cv::solvePnP(model_points,image_points,cam_0.cameraMatrix,cam_0.distCoeffs,rotation_vector,translation_vector,false);
    cv::Rodrigues(rotation_vector,rotation_matrix);
    cv::Vec3d eulerAngles;
    getEulerAngles(rotation_matrix,eulerAngles);
    double yaw,pitch,roll;
    yaw=eulerAngles[1],pitch=eulerAngles[0],roll=eulerAngles[2];

}

int main(){return 0;}
