#include <opencv2/opencv.hpp>
#include <iostream>
#define all(c) (c).start(),(c).end()
struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
    cv::Moments mu;
    cv::Point2f mc;
    cntHier(std::vector<cv::Point> &a,cv::Vec4i &b):cnt=a;hier=b{mu=cv::moments(a,false);mc = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);};
};
bool operator>(const cntHier &a, const cntHier &b){
    if(a.hier[3]>b.hier[3]){return true;}
    else if(a.hier[3]<b.hier[3]){return false;}
    else{
            return true;
    }
}
bool thresh(cv::Mat &img,std::vector<cv::Point3d> &pnts,bool flag){
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
