/*****************************************
 * ParameterReader.h 参数管理类
 * 程序中将有一个该类的全局变量，从parameter.yaml中读取各个参数的值，供其他类使用，方便调试
 ****************************************/

#pragma once
#include "const.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class ParameterReader
{
 public:
    ParameterReader(const string& para_file);
    
    string GetPara(const string& para_name);

 protected:
    string num2string(double d)
    {
        ss.clear();
        ss<<d;
        string s;
        ss>>s;
        return s;
    }

    string num2string(int d)
    {
        ss.clear();
        ss<<d;
        string s;
        ss>>s;
        return s;
    }
    
 protected:
    stringstream ss;
    // configure parameters
    string _data_source; //数据来源
    string _detector_name;//特征相关：检测子名称
    string _descriptor_name; //描述子名称
    int _start_index;    //起始索引
    int _end_index;      //终止索引
    string _grayscale;      //是否以灰度图读取

    int _step_time;      //调试时每一次循环的等待时间
    int _step_time_keyframe; //发现关键帧时的等待时间
    int _save_if_seen, _del_not_seen; //管理特征库的参数

    //图优化参数
    int _optimize_step; //优化步数
    string _robust_kernel;
    

    //特征点相关参数
    string _set_max_depth;  //是否为没有深度数据的点设置最大深度
    double _max_depth;      //最大深度
    double _match_min_dist; //匹配时的最小距离
    int _max_landmark_per_loop; //每一帧增加到库中路标上限
    
    double _max_pos_change;

};

//全局变量指针
extern ParameterReader* g_pParaReader;
