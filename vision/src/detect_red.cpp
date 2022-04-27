#include "vision/detect_red.h"
#include <pluginlib/class_list_macros.h>

namespace detect
{
    void VisionBase::onInit()
    {
        ros::NodeHandle nh("~");
        ros::Time::waitForValid();

        mrs_lib::ParamLoader param_loader(nh, "vision_base");

        param_loader.loadParam("uav_name", _uav_name_);
        

        if (!param_loader.loadedSuccessfully()) {
            ROS_ERROR("[WaypointFlier]: failed to load non-optional parameters!");
            ros::shutdown();
        }

        image_transport::ImageTransport it(nh);

        sub_image_ = it.subscribe("image_in", 1, &VisionBase::image_callback, this);
        

        ROS_INFO_ONCE("[vision_base]: initialized");

        is_initialized_ = true;

        ros::spin();
    }


    void VisionBase::image_callback(const sensor_msgs::ImageConstPtr& image)
    {
        if(!is_initialized_)
            return;

        const std::string color_encoding = "bgr8";

        const cv_bridge::CvImageConstPtr bridge_image_ptr = cv_bridge::toCvShare(image ,color_encoding);
        cv::Mat imageOrigin = bridge_image_ptr->image;

        cv::imshow("Original", imageOrigin);
        
        VisionBase::circles = VisionBase::detect_circle(imageOrigin);

        cv::waitKey(30);
    }

    cv::Mat VisionBase::mask_hsv (cv::Mat imageOrigin)
    {
        cv::Mat img_hsv;
        cv::cvtColor(imageOrigin, img_hsv, cv::COLOR_BGR2HSV);

        cv::Mat mask;
        cv::inRange(img_hsv, cv::Scalar(110,50,0), cv::Scalar(120,120,255), mask);

        return mask;
    }

    std::vector<cv::Vec3f> VisionBase::detect_circle(const cv::Mat imageOrigin)
    {
        
        std::vector<cv::Vec3f> circles1;

        cv::Mat mask = VisionBase::mask_hsv(imageOrigin);

        cv::HoughCircles(mask, circles1, cv::HOUGH_GRADIENT, 1, mask.rows/16,
                         100, 30, 25, 100);
        
        for (size_t i = 0; i < circles1.size(); i++)
        {
            cv::Vec3i c = circles1[i];
            cv::Point center = cv::Point(c[0], c[1]);
            cv::circle(imageOrigin, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
            int radius = c[2];
            cv::circle(imageOrigin, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
        }
        cv::imshow("Circles1", imageOrigin);

        return circles1;
    }

} 
PLUGINLIB_EXPORT_CLASS(detect::VisionBase, nodelet::Nodelet);