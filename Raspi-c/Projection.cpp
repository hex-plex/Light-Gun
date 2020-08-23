#include <opencv2/opencv.hpp>
#include <iostream>
#include "cameraData.cpp"
#define all(c) c.start(),c.end()

float dst(cv::Point3d &a,cv::Point3d &b){
    cv::Point3d c = a-b;
    return cv::sqrt(c.x*c.x + c.y*c.y + c.z*c.z );
}
float dst(cv::Point2d &a,cv::Point2d &b){
    cv::Point2d c = a-b;
    return cv::sqrt(c.x*c.x + c.y*c.y );
}

void getEulerAngles(cv::Mat &rotCameraMatrix,cv::Vec3d &eulerAngles){
    cv::Mat cameraMatrix, rotMatrix,transVect,rotMatrixX,rotMatrixY,rotMatrixZ;
    double* _r = rotCameraMatrix.ptr<double>();
    double projMatrix[12] = {_r[0],_r[1],_r[2],0,
                             _r[3],_r[4],_r[5],0,
                             _r[6],_r[7],_r[8],0};
    cv::decomposeProjectionMatrix(cv::Mat(3,4,CV_64FC1,projMatrix),
                                    cameraMatrix,
                                    rotMatrix,
                                    transVect,
                                    rotMatrixX,
                                    rotMatrixY,
                                    rotMatrixZ,
                                    eulerAngles);
}

bool proj2points(std::vector<cv::Point2d> &image_points,cv::Point2d &centerPoint,cv::Point2d &clickcoor){
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
    cv::Mat RM1 = rotation_matrix.inv()*cam_0.cameraMatrix.inv();
    cv::Mat Rt = rotation_matrix.inv()*translation_vector;
    image_points.push_back(centerPoint);
    cv::Mat finalPoints,imagePoints(image_points);
    std::vector<cv::Point3d> final_points = finalPoints.clone();
    cv::Point3d x3i = (final_points[1]-final_points[0]);x3i.x/=dst(final_points[0],final_points[1]);x3i.y/=dst(final_points[0],final_points[1]);x3i.z/=dst(final_points[0],final_points[1]);
    cv::Point3d y3i = (final_points[2]-final_points[0]);y3i.x/=dst(final_points[0],final_points[2]);y3i.y/=dst(final_points[0],final_points[2]);y3i.z/=dst(final_points[0],final_points[2]);
    cv::Point2d x2i = (model_set.pntrvec[1]-model_set.pntrvec[0]);x2i.x/=dst(model_set.pntrvec[1],model_set.pntrvec[0]);x2i.y/=dst(model_set.pntrvec[1],model_set.pntrvec[0]);
    cv::Point2d y2i = (model_set.pntrvec[2]-model_set.pntrvec[0]);y2i.x/=dst(model_set.pntrvec[2],model_set.pntrvec[0]);y2i.y/=dst(model_set.pntrvec[2],model_set.pntrvec[0]);
    cv::Point2d cnr2i = (model_set.cnrvec[0]-model_set.pntrvec[0]);cnr2i.x/=dst(model_set.cnrvec[0],model_set.pntrvec[0]);cnr2i.y/=dst(model_set.cnrvec[0],model_set.pntrvec[0]);
    cv::Point3d cnr3i = cnr2i.ddot(x2i)*x3i + cnr2i.ddot(y2i)*y3i;
    cv::Point3d resultant = (final_points[4] - cnr3i);resultant.x/=dst(final_points[1],final_points[0]);resultant.y/=dst(final_points[1],final_points[0]);resultant.z/=dst(final_points[1],final_points[0]);
    resultant.x *= 2*centerPoint.x;resultant.y *= 2*centerPoint.x;
    clickcoor = cv::Point2d(resultant.x,resultant.y);
    return (resultant.z<0.01*dst(final_points[1],final_points[0]));
}

int main(){return 0;}
