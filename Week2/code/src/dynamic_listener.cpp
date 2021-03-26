// Written by Nick van der Merwe for 3806ICT GUGC
// s5151332 - nick.vandermerwe@griffithuni.edu.au
#include "ros/ros.h"
#include "turtlesim/Pose.h"

class quadrantPrinter {
    /// Functor to declare where it is. We need to know the initial location
   public:
    quadrantPrinter() : xOrigin{-1}, yOrigin{-1}, firstCall{true} { }

    void operator()(const turtlesim::PoseConstPtr& msg) {
        if (firstCall) {
            this->xOrigin = msg->x;
            this->yOrigin = msg->y;
            firstCall = false;
        }

        ROS_INFO("The turtle is in quadrant [%i]",
                 defineQuadrant(msg->x, msg->y));
    }

    quadrantPrinter(const quadrantPrinter&) = default;

    int defineQuadrant(const float& x, const float& y) {
        /// If its on the border between two then its at
        /// the more upper right quadrant. This isn't clearly
        /// defined in the tasksheet. We can also shortcut
        /// the checks by searching like this instead.
        if (x > this->xOrigin && y > this->yOrigin) {
            return 1;
        }
        if (x > this->xOrigin) {
            return 4;
        }

        if (y > this->yOrigin) {
            return 2;
        }

        return 3;
    }

    float xOrigin, yOrigin;
    bool firstCall{true};
};

int main(int argc, char** argv) {
    /*
     * I'm going to assume you mean which quadrant its in based on its spawn
     * where it follows the unit circle quadrant system. However we also have
     * to assume the first position it reads is the origin of the map, because 
     * looking at the (documentation)[https://wiki.ros.org/turtlesim], there's
     * no way to observe its spawn position.
     * 
     * The reason why we don't assume the origin is at (0,0) is because (0,0) is
     * actually at the top left of the screen. Looking at the sourcecode on github
     * as well, the spawn position can be set in the constructor
     */

    ros::init(argc, argv, "quadrantReporter");
    ros::NodeHandle nodeHandle;
    ros::Subscriber sub =
        nodeHandle.subscribe<turtlesim::PoseConstPtr>("turtle1/pose", 50, quadrantPrinter());

    ros::spin();

    return 0;
}
