cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(cpp_pubsub REQUIRED)

set(msg_files
  "msg/Num.msg"
  "msg/Ocr2lrc.msg"
  "msg/Lrc2ocr.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
 ${msg_files}
 DEPENDENCIES geometry_msgs
)

include_directories(include) # Set PATH for custom header file

add_executable(lrc_node nodes/lrc_node.cpp src/lrc.cpp)
ament_target_dependencies(lrc_node rclcpp std_msgs cpp_pubsub)

add_executable(control_node nodes/control_node.cpp src/scale_truck_control.cpp)
ament_target_dependencies(control_node rclcpp std_msgs cpp_pubsub)

install(TARGETS
  	lrc_node
	control_node
	DESTINATION lib/${PROJECT_NAME}
)

#install(DIRECTORY
#	launch
#	DESTINATION shar/${PROJECT_NAME}
#)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
