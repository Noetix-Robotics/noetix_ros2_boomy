#include "boomy_motion/msg/robot_motor_command_array.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motor_command";
    using T                 = boomy_motion::msg::RobotMotorCommandArray;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
