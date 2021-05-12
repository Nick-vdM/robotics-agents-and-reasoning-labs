// Written by Nick van der Merwe for 3806ICT
// s515332 - nick.vandermerwe@griffithuni.edu.au
#include <cstdlib>
#include <sstream>

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "randomWalker");
    ros::NodeHandle nodeHandle;

    ros::Publisher turtle_pub =
        nodeHandle.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 50);
    ros::Rate loop_rate(2);
    geometry_msgs::Twist msg;

    while (ros::ok()) {
        msg = geometry_msgs::Twist{};
        uint16_t a = rand();  // rand() runs 0 -> 32k

        switch (a % 4) {
            case 0:
                msg.linear.x = 2.0;
                break;
            case 1:
                msg.linear.x = -2.0;
                break;
            case 2:
                msg.angular.z = 2.0;
                break;
            case 3:
                msg.angular.z = 2.0;
                break;
            default:
                break;
        }

        turtle_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
