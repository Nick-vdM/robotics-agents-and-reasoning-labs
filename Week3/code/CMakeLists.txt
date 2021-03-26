cmake_minimum_required(VERSION 3.0.2)
project(week3)

## Compile as C++11, supported in ROS Kinetic and newer
## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    message_generation
    geometry_msgs
)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
add_service_files(
  FILES
  set_target.srv
  distance_to_target.srv
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
  geometry_msgs
)

catkin_package()

include_directories(
    include ${catkin_INCLUDE_DIRS}
)


add_executable(services src/services.cpp)
target_link_libraries(services ${catkin_LIBRARIES})
add_dependencies(services week3_generate_messages_cpp)
