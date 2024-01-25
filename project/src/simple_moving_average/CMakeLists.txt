cmake_minimum_required(VERSION 3.0.2)
project(moving_average)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(filter_node src/filter.cpp)

target_link_libraries(filter_node
  ${catkin_LIBRARIES}
)

catkin_install_python(PROGRAMS
  scripts/sensor.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

