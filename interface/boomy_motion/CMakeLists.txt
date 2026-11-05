cmake_minimum_required(VERSION 3.14)
project(boomy_motion)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(MSG_FILES
    "msg/MotionControlCMD.msg"
    "msg/MotionSetMode.msg"
    "msg/RobotBMSState.msg"
    "msg/RobotIMUData.msg"
    "msg/RobotJoyData.msg"
    "msg/RobotMotorState.msg"
    "msg/RobotMotorStateArray.msg"
    "msg/RobotStatusData.msg"
    "msg/RobotMotorCommand.msg"
    "msg/RobotMotorCommandArray.msg"
    "msg/RobotInfoIMUData.msg"
    "msg/RobotInfoMotorState.msg"
    "msg/RobotInfoMotorStateArray.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME} ${MSG_FILES})

install(FILES ${MSG_FILES} DESTINATION share/${PROJECT_NAME}/msg)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
