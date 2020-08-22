#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv){
	cv::Mat image;
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
	cv::namedWindow("Disp",cv::WINDOW_AUTOSIZE);
	while(1){
		cap>>image;
		if(image.empty()){
			std::cout<<"No image returned"<<std::endl;
			break;
		}
		cv::imshow("Disp",image);
		if(cv::waitKey(1)==27)
			break;
	}
	cap.release();
	cv::destroyAllWindows();
	return 0;
}
