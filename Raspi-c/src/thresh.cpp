#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define all(c) (c).begin(),(c).end()
int RES[2]={640,480};
int DiagL = 800;
struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
    cv::Moments mu;
    cv::Point2f mc;
    cntHier(){};
    cntHier(std::vector<cv::Point> &a,cv::Vec4i &b):cnt(a),hier(b){mu=cv::moments(a,false),mc=cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);}
};
int dst(cv::Point2f &a,cv::Point2f &b){
    cv::Point2f c = a-b;
    return std::sqrt((c.x*c.x) + (c.y*c.y));
}
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

cv::Point2f average(std::vector<cv::Point2f> &cm){
    cv::Point2f tot = cv::Point2f(0.0f,0.0f);
    for(cv::Point2f item : cm){
        tot = tot + item;
    }
    tot.x /= cm.size();
    tot.y /= cm.size();
    return tot;
}

bool condition(const cv::KeyPoint &a,const cv::KeyPoint &b){
    if(a.pt.y-b.pt.y>=0.2*DiagL){return false;}
    else if(a.pt.x - b.pt.x>=0.3*DiagL){return false;}
    else return true;
}

bool thresh(cv::Mat &img,std::vector<cv::Point2d> &pnts,bool flag,int* res){
    RES[0]=res[0];
    RES[1]=res[1];
    /*
    fill in the adaptive thresholding part
    */
    cv::Mat gray;
    cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);
    gray = 255 - gray;
    
    cv::imshow("gray",gray);
    cv::waitKey(0);
    
    cv::SimpleBlobDetector::Params params;
<<<<<<< HEAD
    params.minThreshold = 30;
    params.maxThreshold = 100;
=======
    params.minThreshold = 0;
    params.maxThreshold = 125;
>>>>>>> f33ea37cf03b4909da94043f73d7efcabdb1c4a0
    params.filterByCircularity = true ;
    params.minCircularity = 0.85;
    params.filterByArea = true;
    params.minArea = 5;
<<<<<<< HEAD
    params.maxArea = 30;
=======
    params.maxArea = 3000;
>>>>>>> f33ea37cf03b4909da94043f73d7efcabdb1c4a0
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
    /*
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(img,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);//,cv::CHAIN_APPROX_NONE);
    std::vector< cntHier > arr;
    cv::Point2f refer = cv::Point2f(0.0f,0.0f);
    cv::Point2f minn=cv::Point2f(RES[0],RES[1]),maxx=refer;
    for(int i=0;i<contours.size();i++){
        if(cv::contourArea(contours.at(i))>0.001*RES[0]*RES[1]){
            arr.push_back(cntHier(contours.at(i),hierachy.at(i)));
            if(dst(arr.back().mc,refer)<dst(minn,refer))minn = arr.back().mc;
            if(dst(arr.back().mc,refer)>dst(maxx,refer))maxx = arr.back().mc;
        }
    }
    cv::Point2f diag = maxx-minn;
    DiagL = dst(diag,refer);

    std::sort(all(arr));
    cntHier temp;
    std::vector<cv::Point2f> CenterOfMass;
    std::vector<cv::Point2f> Final;
    cntHier st = arr.at(0);
    for(int i=0;i<arr.size();i++){
        if(dst(st.mc,arr.at(i).mc)<0.05*DiagL){
            CenterOfMass.push_back(arr.at(i).mc);
        }
        else{
            Final.push_back(average(CenterOfMass));
            CenterOfMass.clear();
        }
    }*/
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

