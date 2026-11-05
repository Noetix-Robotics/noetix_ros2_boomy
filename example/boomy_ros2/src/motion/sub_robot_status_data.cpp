#include "boomy_motion/msg/robot_status_data.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/robot_status_data";
    using T                 = boomy_motion::msg::RobotStatusData;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
