#include <opencv2/opencv.hpp>
#include "cameraData.cpp"
#include "thresh.cpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv){
    //cv::Mat im = cv::imread("headPose.jpg");
    cv::VideoCapture cap;
    cap.open(2,cv::CAP_ANY);
    if(!cap.isOpened()){
        std::cout<<"Camera couldnt be opened\n";
        return -1;
    }
    
    std::cout<<"Please press F to select the frame when camera is parrallel to the display\n";
    cv::Mat im;

    bool flag=true;
    cv::namedWindow("Display",cv::WINDOW_AUTOSIZE);
    while(true){
        cap>>im;
        if(!im.data){
            std::cout<<"No image is received from the source\n";
            flag=false;break;
        }
        cv::imshow("Display",im);
        if(cv::waitKey(1)==102){
            break;
        }
    }

    int res[2] = {im.cols, im.rows};

    PointSet r;
    CameraParams c;
    cv::FileStorage fs("refpoints.yaml", cv::FileStorage::READ);
    fs>>r;
    fs.release();

    cv::FileStorage ds("configuredInfo.yaml", cv::FileStorage::READ);
    ds>>c;
    ds.release();

    std::vector<cv::Point2d> image_points;

    thresh(im, image_points, false, res );

    std::vector<cv::Point3d> model_points = r.pntrvec;

    Point2d center = cv::Point2d(im.cols/2, im.rows/2);
    cv::Mat camera_matrix =  c.cameraMatrix;
    cv::Mat dist_coeffs = c.distCoeffs;

    cout<<"Camera Matrix"<<endl<<camera_matrix<<endl;
    
    while(true){
        cap>>im;
        if(!thresh(im, image_points, true, res ))continue;

        cv::Mat rotation_vector;
        cv::Mat translation_vector;

        cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

        vector<Point3d> cen_point3D;
        vector<Point2d> cen_point2D1;
        vector<Point2d> cen_point2D2;
        Point3d temp2(0,0,2000.0);
        Point3d temp1(0,0,10.0);
        for(int i=0;i<4;i++){
            temp1.x+=model_points[i].x;
            temp1.y+=model_points[i].y;
            temp2.x+=model_points[i].x;
            temp2.y+=model_points[i].y;
        }
        temp1.x/=4;
        temp1.y/=4;
        temp2.x/=4;
        temp2.y/=4;
        cen_point3D.push_back(temp1);
    
        projectPoints(cen_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, cen_point2D1);
        cen_point3D.clear();
        cen_point3D.push_back(temp2);
        projectPoints(cen_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, cen_point2D2);

        for(int i=0; i<image_points.size();i++){
            circle(im, image_points.at(i), 3, Scalar(0,0,255), -1);
        }

        cv::line(im, cen_point2D1[0], cen_point2D2[0], cv::Scalar(255,0,0), 2);

        cout<<"Rotation Vector"<<endl<<rotation_vector<<endl;
        cout<<"Translation Vector"<<endl<<translation_vector<<endl;

        cout<<cen_point2D1<<endl;

        cv::imshow("Output", im);
        if(cv::waitKey(1)==113)break;
    
    }

    return 0;
}