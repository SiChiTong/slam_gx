/*****************************************
 * Feature Manager 管理得到的特征并进行帧间配准
 * 管理机制详细过程请参见文档
 ****************************************/
#include <opencv2/core/core.hpp>
#include <Eigen/Core>
#include <g2o/types/slam2d/se2.h>
#include <opencv2/features2d/features2d.hpp>
#include <list>
#include <fstream>
#include "FeatureGrabber.h"

using namespace std;
using namespace cv;
using namespace g2o;

struct LANDMARK
{
    LANDMARK(int ID=-1, Point3f pos=Point3f(0,0,0), Mat desc=Mat(), int exist=0)
    {
        _ID = ID;
        _pos = pos;
        _descriptor = desc;
        _exist_frames = exist;
    }

    Eigen::Vector2d Pose2d() const
    {
        return Vector2d(_pos.x, _pos.y);
    }
    int _ID;
    Point3f _pos;
    Mat _descriptor;
    int _exist_frames;   //连续存在的帧数
};

class FeatureManager
{
 public:
    FeatureManager(int save_if_seen = 10, FeatureGrabberBase* p = NULL, int del_not_seen=-3)
    {
        _pFeatureGrabber = p;
        _save_if_seen = save_if_seen;
        _delete_if_not_seen = del_not_seen;
    }
        
    void Input(vector<KeyPoint>& keypoints, Mat feature_descriptor, SE2& robot_curr);  //输入当前帧的特征点描述子与机器人位置

    void ReportStatus();
    void DumpAllLandmarks(ofstream& fout)
    {
        for (list<LANDMARK>::iterator iter = _landmark_library.begin(); iter !=_landmark_library.end(); iter++)
        {
            fout<<iter->_pos<<endl;
        }
    }

    LANDMARK GetLandmark(int id)
    {
        if (id >= _landmark_library.size())
        {
            return LANDMARK();
        }
        list<LANDMARK>::iterator iter = _landmark_library.begin();
        for (int ix=0; ix<id; ix++)
            iter++;
        return *iter;
    }
    
 private:
    //内部函数
    vector<DMatch> Match(Mat des1, Mat des2);
    SE2 RANSAC(vector<int>& good_landmark_idx, vector<KeyPoint>& keypoints);
 protected:
    FeatureGrabberBase* _pFeatureGrabber;
    
 protected:
    Mat _landmark_pos;   //路标的位置

 public:
    list<LANDMARK> _landmark_buffer;   //缓存
    list<LANDMARK> _landmark_library;  //库

    vector<int> _match_idx;            //该帧中被匹配到的路标的下标
    vector<KeyPoint> _match_keypoints; //图像成功匹配到路标的那些关键点
    // 参数定义
    int _save_if_seen;  //多少帧连续看见该特征，则存储之
    int _delete_if_not_seen;  //缓存中，多少帧未出现此特征，则删除之
    
};
