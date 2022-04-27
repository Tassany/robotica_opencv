cmake_minimum_required(VERSION 3.0.2)
project(detect_pose)


find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  std_msgs
  cv_bridge
  image_geometry
  image_transport
  mrs_lib
  mrs_msgs
)

find_package(OpenCV REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES detect_pose
  CATKIN_DEPENDS roscpp std_msgs nodelet image_transport   mrs_lib mrs_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

install(DIRECTORY include launch src
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
        PATTERN "*~" EXCLUDE
        )

add_library(detect_pose src/detect_pose.cpp)

add_dependencies(
  detect_pose 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(
  detect_pose
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)