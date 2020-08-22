#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

const int max_value_H = 180;
const int max_value = 255;
const cv::String win_cap = "image";
const cv::String win_mask = "mask";
int low_H = 0,low_S = 0, low_V = 0;
int high_H = max_value_H,high_S = max_value, high_V= max_value;

static void l_H_track(int , void*){low_H = std::min(high_H-1,low_H);cv::setTrackbarPos("LOW H",win_mask,low_H);}
static void h_H_track(int , void*){high_H = std::max(high_H,low_H+1);cv::setTrackbarPos("HIGH H",win_mask,high_H);}
static void l_S_track(int , void*){low_S = std::min(high_S-1,low_S);cv::setTrackbarPos("LOW S",win_mask,low_S);}
static void h_S_track(int , void*){high_S = std::max(high_S,low_S+1);cv::setTrackbarPos("HIGH S",win_mask,high_S);}
static void l_V_track(int , void*){low_V = std::min(high_V-1,low_V);cv::setTrackbarPos("LOW V",win_mask,low_V);}
static void h_V_track(int , void*){high_V = std::max(high_V,low_V+1);cv::setTrackbarPos("HIGH V",win_mask,high_V);}

int main(int argc, char** argv){
	cv::Mat image,mask;
	cv::VideoCapture cap;
	cap.open(0,cv::CAP_ANY);
	if(!cap.isOpened()){
		std::cout << "Could not open the camera" <<std::endl;
		return -1;
	}
	std::cout<<"BRIGHTNESS "<<cap.set(cv::CAP_PROP_BRIGHTNESS,20)<<"\n";
	//std::cout<<"CONTRAST "<<cap.set(cv::CAP_PROP_CONTRAST,10)<<"\n";
	std::cout<<"EXPOSURE "<<cap.get(cv::CAP_PROP_EXPOSURE)<<"\n";
	std::cout<<"SHARPNESS "<<cap.get(cv::CAP_PROP_SHARPNESS)<<"\n";
	cv::namedWindow(win_cap,cv::WINDOW_AUTOSIZE);
	cv::namedWindow(win_mask,cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("LOW H",win_mask,&low_H,max_value_H, l_H_track);
	cv::createTrackbar("HIGH H",win_mask,&high_H,max_value_H, h_H_track);
	cv::createTrackbar("LOW S",win_mask,&low_S,max_value, l_S_track);
	cv::createTrackbar("HIGH S",win_mask,&high_S,max_value, h_S_track);
	cv::createTrackbar("LOW V",win_mask,&low_V,max_value, l_V_track);
	cv::createTrackbar("HIGH V",win_mask,&high_V,max_value, h_V_track);
	while(1){
		cap>>image;
		if(image.empty()){
			std::cout<<"No image returned"<<std::endl;
			break;
		}
		cv::cvtColor(image,image,cv::COLOR_BGR2HSV);
		cv::inRange(image,cv::Scalar(low_H,low_S,low_V),cv::Scalar(high_H,high_S,high_V),mask);
		cv::imshow(win_cap,image);
		cv::imshow(win_mask,mask);
		if(cv::waitKey(1)==27)
			break;
	}
	cap.release();
	cv::destroyAllWindows();
	return 0;
}
