#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){
    cv::Mat im = cv::imread("headPose.jpg");

    std::vector<cv::Point2d> image_points;
    image_points.push_back(cv::Point2d(359,391));
    image_points.push_back(cv::Point2d(399, 561));
    image_points.push_back(cv::Point2d(337, 297));
    image_points.push_back(cv::Point2d(513, 301));
    image_points.push_back(cv::Point2d(345, 465));
    image_points.push_back(cv::Point2d(453, 469));

    std::vector<cv::Point3d> model_points;
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));
    model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));
    model_points.push_back(cv::Point3d(-255.0f, 170.0f, -135.0f));
    model_points.push_back(cv::Point3d(255.0f, 170.0f, -135.0f));
    model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));
    model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));

    double focal_length = im.cols;
    Point2d center = cv::Point2d(im.cols/2, im.rows/2);
    cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0, focal_length, center.y, 0 , 0, 1 );
    cv::Mat dist_coeffs = cv::Mat::zeros(4,1, cv::DataType<double>::type);

    cout<<"Camera Matrix"<<endl<<camera_matrix<<endl;
    
    cv::Mat rotation_vector;
    cv::Mat translation_vector;

    cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

    vector<Point3d> nose_end_point3D;
    vector<Point2d> nose_end_point2D;
    nose_end_point3D.push_back(Point3d(0,0,1000.0));

    projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);

    for(int i=0; i<image_points.size();i++){
        circle(im, image_points.at(i), 3, Scalar(0,0,255), -1);
    }

    cv::line(im, image_points[0], nose_end_point2D[0], cv::Scalar(255,0,0), 2);

    cout<<"Rotation Vector"<<endl<<rotation_vector<<endl;
    cout<<"Translation Vector"<<endl<<translation_vector<<endl;

    cout<<nose_end_point2D<<endl;

    cv::imshow("Output", im);
    cv::waitKey(0);


    return 0;
}