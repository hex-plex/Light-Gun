#include <opencv2/opencv.hpp>
#include <iostream>
#define all(c) (c).begin(),(c).end()

int WIDTH= 0,HEIGTH=0;
int zone = 0;
int dst(cv::Point z){
    return pow(z.x,2) + pow(z.y,2);
}
bool cp(cv::KeyPoint a,cv::KeyPoint b){
    if(zone==0){
        return dst(a.pt) < dst(b.pt);
    } else if(zone == 1){
        return dst(a.pt-cv::Point(WIDTH,0))<dst(b.pt-cv::Point(WIDTH,0));
    } else if(zone == 2){
        return dst(a.pt-cv::Point(0,HEIGTH))<dst(b.pt-cv::Point(0,HEIGTH));
    } else {
        return dst(a.pt-cv::Point(WIDTH,HEIGTH))<dst(b.pt-cv::Point(WIDTH,HEIGTH));
    }
}
int quadrant(cv::KeyPoint z){
    return (z.pt.x > int(WIDTH/2)) + 2*(z.pt.y > int(HEIGTH/2));
}
int main(int argc, char** argv){
	cv::Mat image,gray,im;
	cv::VideoCapture cap;
	cap.open(0,cv::CAP_ANY);
	if(!cap.isOpened()){
		std::cout << "Could not open the camera" <<std::endl;
		return -1;
	}
	std::cout<<"BRIGHTNESS "<<cap.set(cv::CAP_PROP_BRIGHTNESS,40)<<"\n";
	//std::cout<<"CONTRAST "<<cap.set(cv::CAP_PROP_CONTRAST,10)<<"\n";
	std::cout<<"EXPOSURE "<<cap.get(cv::CAP_PROP_EXPOSURE)<<"\n";
	std::cout<<"SHARPNESS "<<cap.get(cv::CAP_PROP_SHARPNESS)<<"\n";
    WIDTH = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    HEIGTH = cap.get(cv::CAP_PROP_FRAME_HEIGTH);
	cv::namedWindow("Disp",cv::WINDOW_AUTOSIZE);
    cv::SimpleBlobDetector::Params params;
    params.minThreshold=100;
    params.maxThreshold=200;
    params.filterByCircularity = true;
    params.minCircularity=0.75;
    params.filterByArea = true;
    params.minArea = 10;
    params.maxArea = 25;
    params.filterByConvexity = false;
    params.filterByInertia= false;
    //params.minConvexity=0.1;
    cv::Ptr<cv::SimpleBlobDetector>  detector= cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;
    std::vector <std::vector <cv::KeyPoint> > quad(4,keypoints);
	while(1){
        keypoints.clear();
        for(int i = 0; i < 4; i++)
            quad.at(i).clear();
		cap>>image;
		if(image.empty()){
			std::cout<<"No image returned"<<std::endl;
			break;
		}
        cv::cvtColor(image,gray,cv::COLOR_BGR2GRAY);
        gray = 255 - gray;
        detector->detect(gray,keypoints);
        for(int i=0; i<(int)keypoints.size();i++){
            quad.at(quadrant(keypoints.at(i)).push_back(keypoints.at(i));
        }
        for(int i=0; i<4; i++){
            zone=i;
            std::sort(all(quad.at(i)),cp);
            if (quad.at(i).size()!=0){
                cv::Point ctr(quad.at(i).at(0).pt);
                cv::circle(image, ctr,5 , cv::Scalar(0,0,255),-1);
            }
        }
        //cv::drawKeypoints(image,keypoints,image,cv::Scalar(255,0,0),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::imshow("Disp",image);
		if(cv::waitKey(1)==27)
			break;
	}
	cap.release();
	cv::destroyAllWindows();
	return 0;
}
