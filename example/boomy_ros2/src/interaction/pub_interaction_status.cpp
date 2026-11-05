#include "boomy_interaction/msg/interaction_status.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/interaction_status";
    using T                 = boomy_interaction::msg::InteractionStatus;
    T sample;
    boomy_interaction::msg::Header header;
    header.message_id   = 1001;
    header.timestamp_us = 1710000000000000ULL;
    header.sn           = "";
    sample.header       = header;
    sample.value        = 0;
    sample.reason       = 0;
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
