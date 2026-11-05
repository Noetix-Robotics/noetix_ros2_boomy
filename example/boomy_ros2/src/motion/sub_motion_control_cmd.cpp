#include "boomy_motion/msg/motion_control_cmd.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motion_control_cmd";
    using T                 = boomy_motion::msg::MotionControlCMD;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
