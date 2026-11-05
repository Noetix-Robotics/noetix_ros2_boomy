#include "boomy_interaction/msg/common_config.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/common_config_get";
    using T                 = boomy_interaction::msg::CommonConfig;
    T sample;
    boomy_interaction::msg::Header header;
    header.message_id    = 1001;
    header.timestamp_us  = 1710000000000000ULL;
    header.sn            = "BOOMY-SDK-SAMPLE";
    sample.header        = header;
    sample.common_config = R"({"timeout_without_conversation":60000,"default_language":"auto"})";
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
