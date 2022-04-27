#ifndef DETECT_POSE_H
#define DETECT_POSE_H

#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>


/* some OpenCV includes */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* ROS includes for working with OpenCV and images */
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <image_geometry/pinhole_camera_model.h>

/* custom helper functions from our library */
#include <mrs_lib/param_loader.h>
#include <mrs_lib/transformer.h>
 
namespace detect {
 
class VisionBase : public nodelet::Nodelet {
    
public:

    virtual void onInit();

private:
    std::string _uav_name_;
    image_transport::Subscriber sub_image_;
    bool is_initialized_ = false;
    void image_callback(const sensor_msgs::ImageConstPtr& image);


    cv::Mat mask_hsv (cv::Mat);
    std::vector<cv::Vec3f> detect_circle(const cv::Mat);
    std::vector<cv::Vec3f> circles;


};
 
}

#endif