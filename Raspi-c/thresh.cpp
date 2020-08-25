#include <opencv2/opencv.hpp>
#include <iostream>
#define all(c) (c).start(),(c).end()
struct CV_EXPORTS cntHier{
    std::vector <cv::Point> cnt;
    cv::Vec4i hier;
    cv::Moments mu;
    cv::Point2f mc;
    cntHier(std::vector<cv::Point> &a,cv::Vec4i &b):cnt=a;hier=b{};
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
    std::vector<cv::Moments> mu(4);
    std::vector<cv::Point2f> mc(4);
    for(int i = 0; i<4;i++){
        temp = arr.at(i);
        cnt = temp.cnt;
        mu[i] = cv::moments(cnt,false);
        mc[i] = cv::Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
    }
    return flag;
}

int main(){return 0;}
