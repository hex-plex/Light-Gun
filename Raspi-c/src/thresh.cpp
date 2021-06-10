#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define all(c) (c).begin(),(c).end()


int RES[2]={640,480};
int DiagL = 800;

/**
*    \Struct for handling Contours easily in tandom with heirarchy 
*/
struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
    cv::Moments mu;
    cv::Point2f mc;
    cntHier(){};
    cntHier(std::vector<cv::Point> &a,cv::Vec4i &b):cnt(a),hier(b){mu=cv::moments(a,false),mc=cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);}
};

/**
*   \Returns distance between two Point2f's
*/
int dst(cv::Point2f &a,cv::Point2f &b){
    cv::Point2f c = a-b;
    return std::sqrt((c.x*c.x) + (c.y*c.y));
}

/**
*   \Comparision operator for the custom datastructs
*/
bool operator<(const cntHier &a, const cntHier &b){
    bool flag=false;
    cv::Point2f amc = a.mc,bmc=b.mc;
    if (dst(amc,bmc)<0.07*DiagL){
        if(a.hier[3]>b.hier[3]){return false;}
        else if(a.hier[3]<b.hier[3]){return true;}
        else if(cv::contourArea(a.cnt)<=cv::contourArea(b.cnt)){return false;}
    }
    if(a.mc.y-b.mc.y>=0.2*DiagL){return false;}
    else if(a.mc.x - b.mc.x >= 0.3*DiagL){return false;}
    else return true;

}

/**
*   \Averages set of points for getting center of mass of Keypoints
*/
cv::Point2f average(std::vector<cv::Point2f> &cm){
    cv::Point2f tot = cv::Point2f(0.0f,0.0f);
    for(cv::Point2f item : cm){
        tot = tot + item;
    }
    tot.x /= cm.size();
    tot.y /= cm.size();
    return tot;
}

/**
*   \Comparision operator for keypoints
*/
bool condition(const cv::KeyPoint &a,const cv::KeyPoint &b){
    if(a.pt.y-b.pt.y>=0.2*DiagL){return false;}
    else if(a.pt.x - b.pt.x>=0.3*DiagL){return false;}
    else return true;
}


/**
*   \Thresholds points in the image and sorts them in specified order
*/
bool thresh(cv::Mat &img,std::vector<cv::Point2d> &pnts,bool flag,int* res){
    RES[0]=res[0];
    RES[1]=res[1];
    /*
    fill in the adaptive thresholding part
    */
    cv::Mat gray;
    cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);
    
    cv::GaussianBlur(gray, gray, cv::Size(5,5), 0);

    cv::threshold( gray, gray, 105, 255, 0 ); // Param 1 threshold value
    double min, max;
    cv::minMaxIdx(gray, &min, &max);
    //std::cout<<"Max "<<max<<" Min "<<min<<"\n";
    
    
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, 
                                                cv::Size(5, 5),
                                                cv::Point(2,2)
                            ); // Param 2 Stride lenght 
    
    cv::erode(gray, gray, element);
    cv::dilate(gray, gray, element);

    // cv::imshow("Yo",gray);
    // cv::waitKey(1);
    
    gray = 255 - gray;



    cv::SimpleBlobDetector::Params params;
    params.minThreshold = 50;
    params.maxThreshold = 255;
    params.filterByCircularity = true ;
    params.minCircularity = 0.8;
    params.filterByArea = true;
    params.minArea = 3;
    params.maxArea = 100;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(gray,keypoints);
    
    
    std::vector<cv::Point2f> Final;
    cv::Point2f refer = cv::Point2f(0.0f,0.0f);
    cv::Point2f minn=cv::Point2f(RES[0],RES[1]),maxx=refer;
    if (keypoints.size()<4)return false;
    for (int i=0;i<keypoints.size();i++){
        if(dst(keypoints.at(i).pt,refer)<dst(minn,refer))minn = keypoints.at(i).pt;
        if(dst(keypoints.at(i).pt,refer)>dst(maxx,refer))maxx = keypoints.at(i).pt;
    }
    cv::Point2f diag = maxx-minn;
    DiagL = dst(diag,refer);
    std::sort(all(keypoints),condition);
    for(int i=0;i<std::min(4,(int)keypoints.size());i++){
        Final.push_back(keypoints.at(i).pt);
    }
   
    pnts.clear();
    for(int i = 0; i<4;i++){
        pnts.push_back(cv::Point2d((double)Final.at(i).x,(double)Final.at(i).y));
    }
    if(flag){
        cv::Mat dat = img.clone();
        for(int i=0;i<4;i++){
            cv::circle(dat,cv::Point((int)Final.at(i).x,(int)Final.at(i).y),10,cv::Scalar(255,0,0),-1,8,0);
        }
        cv::imshow("Instance",dat);
        cv::waitKey(0);
        cv::destroyWindow("Instance");
    }
    return true;
}

