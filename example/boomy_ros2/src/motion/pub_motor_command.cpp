#include "boomy_motion/msg/robot_motor_command_array.hpp"
#include "common/ros2_example_common.hpp"

#include <string>
#include <vector>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motor_command";
    using T                 = boomy_motion::msg::RobotMotorCommandArray;
    T sample;
    sample.motorcmds.reserve(21);
    for (uint16_t i = 0; i < 21; ++i) {
        boomy_motion::msg::RobotMotorCommand command;
        command.pos      = 0.0;
        command.vel      = 0.0;
        command.tau      = 0.0;
        command.kp       = 20.0;
        command.kd       = 0.5;
        command.motor_id = i;
        sample.motorcmds.push_back(command);
    }
    sample.timestamp = 1710000000000000LL;
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
