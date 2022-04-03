#include <stdio.h>
#include <detect_red/detect_red.h>
#include <opencv2/opencv.hpp>
#include <pluginlib/class_list_macros.h>

using namespace cv;
using namespace std;

namespace Detect_red
{
    void detect_red::onInit(){
        ros::NodeHandle nh("~");

        ros::Time::waitForValid();

        ros::spin();

    }

}
PLUGINLIB_EXPORT_CLASS(Detect_red::detect_red,nodelet::Nodelet);