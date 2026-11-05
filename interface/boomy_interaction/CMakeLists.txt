cmake_minimum_required(VERSION 3.14)
project(boomy_interaction)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(MSG_FILES
    "msg/AudioControl.msg"
    "msg/AudioStreamFrame.msg"
    "msg/AudioVolume.msg"
    "msg/CommonConfig.msg"
    "msg/Header.msg"
    "msg/InteractionControl.msg"
    "msg/InteractionError.msg"
    "msg/InteractionStatus.msg"
    "msg/VideoControl.msg"
    "msg/VideoStream.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME} ${MSG_FILES})

install(FILES ${MSG_FILES} DESTINATION share/${PROJECT_NAME}/msg)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
