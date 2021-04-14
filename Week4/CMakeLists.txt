cmake_minimum_required(VERSION 3.0.2)
project(week4)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_generation
  roscpp
  rospy
  std_msgs
  gazebo_msgs
)

# Generate services in the 'srv' folder
add_service_files(
  FILES
  st.srv
  dtt.srv
)

# Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
)

catkin_package()

include_directories(
 include  ${catkin_INCLUDE_DIRS}
)

add_executable(services_week4 src/services.cpp)
target_link_libraries(services_week4 ${catkin_LIBRARIES})
add_dependencies(services_week4 week4_generate_messages_cpp)
