#include "boomy_interaction/msg/interaction_control.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/interaction_control";
    using T                 = boomy_interaction::msg::InteractionControl;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
