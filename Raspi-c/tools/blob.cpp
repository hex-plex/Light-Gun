#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){
	cv::Mat image,gray,im;
	//cv::VideoCapture cap;
	//cap.open(0,cv::CAP_ANY);
	//if(!cap.isOpened()){
		//std::cout << "Could not open the camera" <<std::endl;
		//return -1;
	//}
	//std::cout<<"BRIGHTNESS "<<cap.set(cv::CAP_PROP_BRIGHTNESS,10)<<"\n";
	//std::cout<<"CONTRAST "<<cap.set(cv::CAP_PROP_CONTRAST,10)<<"\n";
	//std::cout<<"EXPOSURE "<<cap.get(cv::CAP_PROP_EXPOSURE)<<"\n";
	//std::cout<<"SHARPNESS "<<cap.get(cv::CAP_PROP_SHARPNESS)<<"\n";
	cv::namedWindow("Disp",cv::WINDOW_AUTOSIZE);
    cv::SimpleBlobDetector::Params params;
    params.minThreshold=70;
    params.maxThreshold=200;
    params.filterByCircularity = true;
    params.minCircularity=0.75;
    params.filterByArea = true;
    params.minArea = 2;
    params.maxArea = 20;
    params.filterByConvexity = false;
    params.filterByInertia= false;
    //params.minConvexity=0.1;

    cv::Ptr<cv::SimpleBlobDetector>  detector= cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;
	for(int i = 0;i<24;i++){
        image = cv::imread("../raspi-feed/capture"+std::to_string(i)+".jpg");
        keypoints.clear();
		//cap>>image;
        cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
        gray = 255 - gray;
        detector->detect(gray,keypoints);
        cv::drawKeypoints(image,keypoints,image,cv::Scalar(0,0,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Disp",image);
		int k = cv::waitKey(0);
		if(k == 111){
            cv::imwrite("../raspi-feed/detect"+std::to_string(i)+".jpg",image);
		}

	}
	//cap.release();
	cv::destroyAllWindows();
	return 0;
}
