#include <ros/ros.h>
#include <signal.h>
#include <nodelet/nodelet.h>

namespace Detect_red
{

    class detect_red: public nodelet::Nodelet
    {
        public:
            virtual void onInit();
        
        private:
    };

}