#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define all(c) (c).start(),(c).end()
int RES[2]={640,480};
struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
    cv::Moments mu;
    cv::Point2f mc;
    cntHier(std::vector<cv::Point> &a,cv::Vec4i &b):cnt=a;hier=b{mu=cv::moments(a,false);mc = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);};
};
int dst(cv::Point2f &a,cv::Point2f &b){
    cv::Point2f c = a-b;
    return std::sqrt((c.x*c.x) + (c.y*c.y));
}
bool operator>(const cntHier &a, const cntHier &b){
    bool flag=false;
    if (dst(a,b)<0.2*std::min(RES[0],RES[1])){
        if(a.hier[3]>b.hier[3]){return true;}
        else if(a.hier[3]<b.hier[3]){return false;}
        else{
            flag=true;
        }
    }
    if(a.mc.x-b.mc.x >= 0){
        if(a.mc.y-b.mc.y>=0.05*std(min(RES[0],RES[1]))){return true;}
        else()
    }
    else{}

}
bool thresh(cv::Mat &img,std::vector<cv::Point3d> &pnts,bool flag,int* res){
    RES[0]=res[0];
    RES[1]=res[1];
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(img,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);//,cv::CHAIN_APPROX_NONE);
    std::vector< cntHier > arr;
    for(int i=0;i<contours.size();i++){
        arr.push_back(cntHier(contours.at(i),hierachy.at(i)));
    }
    std::sort(all(arr));
    cntHier temp;
    std::vector<cv::Point> cnt;
    pnts.clear();
    for(int i = 0; i<4;i++){
        temp = arr.at(i);
        pnts.push_back(cv::Point3d(temp.mc.x,temp.mc.y,10));
    }

    return flag;
}

int main(){return 0;}
