#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat imgHSV,mask;
int hmin = 0, smin = 110, vmin =  153;
int hmax = 19, smax = 240, vmax = 255;

int main()
{
    // Mat img = imread("maca.jpg");
    Mat frame;
    VideoCapture video_load(0);
    // cvtColor(img,imgHSV,COLOR_BGR2HSV);

    namedWindow("Trackbars",(640,200));

    createTrackbar("Hue min", "Trackbars", &hmin,179);
    createTrackbar("Hue max", "Trackbars", &hmax,179);
    createTrackbar("Sat min", "Trackbars", &smin,255);
    createTrackbar("Sat max", "Trackbars", &smax,255);
    createTrackbar("Val min", "Trackbars", &vmin,255);
    createTrackbar("Val max", "Trackbars", &vmax,255);
    video_load.open(0,cv::CAP_ANY);
    // red -> hue min: 151, sat min:47, val min:0
    while(true){
        video_load.read(frame);

        Mat convert_to_HSV;
        cvtColor(frame, convert_to_HSV, COLOR_BGR2HSV);
        
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);
        inRange(convert_to_HSV,lower,upper,mask);
    
        // imshow("Image",img);
        // imshow("Image HSV",imgHSV);
        // imshow("Image mask",mask);

        imshow("Video Real",frame);
        imshow("Video",mask);
        waitKey(1);
    }

    return 0;
}