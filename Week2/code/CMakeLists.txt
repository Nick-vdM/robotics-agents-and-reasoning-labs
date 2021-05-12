cmake_minimum_required(VERSION 3.0.2)
project(week2)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
################################################
## Declare ROS messages, services and actions ##
################################################
## Generate services in the 'srv' folder
# add_message_files(
#   DIRECTORY msg
#   FILES Num.msg
#   )
#   add_service_files(
#   DIRECTORY srv
#   FILES  AddTwoInts.srv
#   )


## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)
catkin_package()

include_directories(
    include  ${catkin_INCLUDE_DIRS}
)

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})
add_dependencies(publisher week2_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener week2_generate_messages_cpp)

