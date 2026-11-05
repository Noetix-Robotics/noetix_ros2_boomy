#include "boomy_interaction/msg/interaction_status.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/interaction_status";
    using T                 = boomy_interaction::msg::InteractionStatus;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
