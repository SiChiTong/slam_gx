#include "ParameterReader.h"
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "const.h"

using namespace std;

ParameterReader* g_pParaReader;

ParameterReader::ParameterReader(const string& para_file )
{
    if (debug_info)
    {
        cout<<"init parameterReader, file addr = "<<
            para_file<<endl;
    }

    ifstream fin(para_file.c_str());

    YAML::Parser parser(fin);
    YAML::Node config;
    try {
        parser.GetNextDocument(config);
    } catch (YAML::ParserException& e)
    {
        cerr<<e.what()<<"\n";
        return ;
    }

    //直接从config中读信息即可
    config[ "data_source" ] >> _data_source;
    config[ "detector_name" ] >> _detector_name;
    config[ "descriptor_name" ] >> _descriptor_name;
    config[ "start_index" ] >> _start_index;
    config[ "end_index" ] >> _end_index;
    config[ "grayscale" ] >> _grayscale;
    config[ "step_time" ] >> _step_time;
    config[ "save_if_seen" ] >> _save_if_seen;
    config[ "del_not_seen" ] >> _del_not_seen;
    config[ "optimize_step" ] >> _optimize_step;
    config[ "robust_kernel" ] >> _robust_kernel;
    if (_end_index < _start_index)
    {
        cerr<<"end index should be larger than start index."<<endl;
        return;
    }

    config[ "set_max_depth"] >> _set_max_depth;
    config[ "max_depth" ] >> _max_depth;
    config[ "max_landmark_per_loop" ] >> _max_landmark_per_loop;
    config[ "max_pos_change" ] >> _max_pos_change;
    config[ "step_time_keyframe" ] >> _step_time_keyframe;
}

string ParameterReader::GetPara( const string& para_name )
{
    if (para_name == string("detector_name"))
        return _detector_name;
    if (para_name == string("descriptor_name"))
        return _descriptor_name;
    if (para_name == string("data_source"))
        return _data_source;
    if (para_name == string("step_time"))
        return num2string(_step_time);
    if (para_name == string("save_if_seen"))
        return num2string(_save_if_seen);
    if (para_name == string("del_not_seen"))
        return num2string( _del_not_seen );
    if (para_name == string("optimize_step"))
        return num2string(_optimize_step);
    if (para_name == string("robust_kernel"))
        return _robust_kernel;
    if (para_name == string("set_max_depth"))
        return _set_max_depth;
    if (para_name == string("match_min_dist"))
        return num2string(_match_min_dist);
    if (para_name == string("max_landmark_per_loop"))
        return num2string(_max_landmark_per_loop);
    if (para_name == string("max_pos_change"))
        return num2string(_max_pos_change);
    if (para_name == string("grayscale"))
        return _grayscale;
    if (para_name == string("start_index"))
        return num2string(_start_index);
    if (para_name == string("end_index"))
        return num2string(_end_index);
    if (para_name == string("step_time_keyframe"))
        return num2string(_step_time_keyframe);
    cerr<<"Unknown parameter: "<<para_name<<endl;
    return string("unknown_para_name");
}
