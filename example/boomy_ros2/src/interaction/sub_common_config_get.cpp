#include "boomy_interaction/msg/common_config.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/common_config_get";
    using T                 = boomy_interaction::msg::CommonConfig;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
