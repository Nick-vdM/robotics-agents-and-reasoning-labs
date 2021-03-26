// Written by Nick van der Merwe for 3806ICT GUGC
// s5151332 - nick.vandermerwe@griffithuni.edu.au
#include "ros/ros.h"
#include "turtlesim/Pose.h"

constexpr uint8_t XORIGIN = 5.544445;
constexpr uint8_t YORIGIN = 5.544445;

int defineQuadrant(const float& x, const float& y) {
    /// If its on the border between two then its at
    /// the more upper right quadrant. This isn't clearly
    /// defined in the tasksheet. We can also shortcut
    /// the checks by searching like this instead.
    if (x > XORIGIN && y > YORIGIN) {
        return 1;
    }
    if (x > XORIGIN) {
        return 4;
    }

    if (y > YORIGIN) {
        return 2;
    }

    return 3;
}

void quadrantPrinter(const turtlesim::PoseConstPtr msg) {
    ROS_INFO("Its currently at quadrant %i", defineQuadrant(msg->x, msg->y));
}

int main(int argc, char** argv) {
    /*
     * After reading the sourcecode of turtle.sim at
     * https://github.com/ros/ros_tutorials/blob/noetic-devel/turtlesim/src/
     * I realised that regardless of the monitor resolution, the turtle always
     * spawns in the same place. We'll use this as the origin
     */

    ros::init(argc, argv, "quadrantReporter");
    ros::NodeHandle nodeHandle;
    ros::Subscriber sub =
        nodeHandle.subscribe("turtle1/pose", 50, quadrantPrinter);

    ros::spin();

    return 0;
}
