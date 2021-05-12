#include "ros/ros.h"
#include "week4/st.h"
#include "week4/dtt.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Pose.h"
#include "gazebo_msgs/ModelStates.h"
#include <cmath>

geometry_msgs::Vector3 Vector3Ctor(double x, double y, double z){
    // For some reason the vector3 ctor is broken so here's a custom one
    geometry_msgs::Vector3 toReturn;
    toReturn.x = x;
    toReturn.y = y;
    toReturn.z = z;
    return toReturn;
}

geometry_msgs::Vector3 target;

bool setTargetFunction(week4::st::Request & req,
        week4::st::Response & res){
    // Set the target to always stay the same
    // World runs from 0->11.0 in both x and y
    target.x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 11;
    target.y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 11;
    target.z = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 11;
    res.location = Vector3Ctor(target.x, target.y, target.z);

    ROS_INFO("Set target to %f %f", res.location.x, res.location.y);
    return true;
}


double euclideanDistance(geometry_msgs::Vector3 & point,
        geometry_msgs::Pose & pose){
    return sqrt(
        pow(point.x - pose.position.x, 2) +
        pow(point.y - pose.position.y, 2) +
        pow(point.z - pose.position.z, 2)
    );
}

geometry_msgs::Pose turtlePose;

void setTurtlePose(const gazebo_msgs::ModelStates& msg){
    int index = 0; // because we want to do a foreach
    // while knowing the index
    for(auto & s : msg.name){
        if(s == "bowl"){
            turtlePose = msg.pose[index];
            return;
        }
        else{
            index++;
        }
    }
    ROS_INFO("An error occured: Nothing called bowl was found");
}

bool distanceToTargetFunction(week4::dtt::Request & req,
    week4::dtt::Response & res){
    res.relative_distance = euclideanDistance(target, turtlePose);
    res.robot_location = Vector3Ctor(turtlePose.position.x, 
            turtlePose.position.y, turtlePose.position.z);
    res.target_location = target;
    return true;
}


int main(int argc, char **argv){
    srand(time(NULL));
    ros::init(argc, argv, "services_server");
    ros::NodeHandle nodeHandle;

    ros::ServiceServer setTargetService =
        nodeHandle.advertiseService("st", setTargetFunction);
    ros::ServiceServer setDistanceToTargetService =
        nodeHandle.advertiseService("dtt", distanceToTargetFunction);
    ros::Subscriber turtlePoseSubscriber = 
        nodeHandle.subscribe("gazebo/model_states", 50, setTurtlePose);
    ROS_INFO("Ready to manage erequests");

    ros::spin();

    return 0;
}
