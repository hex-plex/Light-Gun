#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define all(c) (c).start(),(c).end()
int RES[2]={640,480};
int DiagL = 800;
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
    if (dst(a,b)<0.07*DiagL){
        if(a.hier[3]>b.hier[3]){return true;}
        else if(a.hier[3]<b.hier[3]){return false;}
        else(cv::contourArea(a)<=cv::contourArea(b.cnt)){return true;}
    }
    if(a.mc.y-b.mc.y>=0.2*DiagL){return true;}
    else if(a.mc.x - b.mc.x >= 0.3*DiagL){return true;}
    else return false;

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

bool thresh(cv::Mat &img,std::vector<cv::Point2d> &pnts,bool flag,int* res){
    RES[0]=res[0];
    RES[1]=res[1];
    /*
    fill in the adaptive thresholding part
    */

    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierachy;
    cv::findContours(img,contours,hierachy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);//,cv::CHAIN_APPROX_NONE);
    std::vector< cntHier > arr;
    cv::Point2f refer = cv::Point2f(0.0f,0.0f);
    cv::Point2f minn=cv::Point2f(RES[0],RES[1]),maxx=refer;
    for(int i=0;i<contours.size();i++){
        arr.push_back(cntHier(contours.at(i),hierachy.at(i)));
        if(dst(a.at(i).mc,refer)<dst(minn,refer))minn = a.at(i).mc;
        if(dst(a.at(i).mc,refer)>dst(maxx,refer))maxx = a.at(i).mc;
    }
    cv::Point2f diag = maxx-minn;
    DiagL = dst(diag,refer);

    std::sort(all(arr));
    cntHier temp;
    std::vector<cv::Point2f> CenterOfMass;
    std::vector<cv::Point2f> Final;
    cntHier st = arr.at(0);
    for(int i=0;i<arr.size();i++){
        if(dst(st,arr.at(i))<0.05*DiagL){
            CenterOfMass.push_back(arr.at(i).mc);
        }
        else{
            Final.push_back(average(CenterOfMass));
            CenterOfMass.clear();
        }
    }
    pnts.clear();
    for(int i = 0; i<4;i++){
        pnts.push_back(cv::Point2d((double)Final.at(i).x,(double)Final.at(i).y));
    }
    if(flag){
        cv::Mat dat = img.clone();
        for(int i=0;i<4;i++){
            cv::circle(dat,cv::Point((int)Final.at(i).x,(int)Final.at(i).y),radius=10,cv::Scalar(255,0,0),-1,8,0);
        }
        cv::imshow("Instance",img)
        cv::waitKey(0);
        cv::destroyWindow("Instance");
    }
    return true;
}

int main(){return 0;}
