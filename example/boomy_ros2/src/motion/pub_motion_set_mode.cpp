#include "boomy_motion/msg/motion_set_mode.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motion_set_mode";
    using T                 = boomy_motion::msg::MotionSetMode;
    T sample;
    sample.mode = 1;
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
