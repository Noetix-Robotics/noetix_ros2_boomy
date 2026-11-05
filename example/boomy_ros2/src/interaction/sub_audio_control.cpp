#include "boomy_interaction/msg/audio_control.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/audio_control";
    using T                 = boomy_interaction::msg::AudioControl;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
