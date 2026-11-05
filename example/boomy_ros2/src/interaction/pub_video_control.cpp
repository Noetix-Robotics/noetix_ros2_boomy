#include "boomy_interaction/msg/video_control.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/video_control";
    using T                 = boomy_interaction::msg::VideoControl;
    T sample;
    boomy_interaction::msg::Header header;
    header.message_id   = 1001;
    header.timestamp_us = 1710000000000000ULL;
    header.sn           = "";
    sample.header       = header;
    sample.type         = 0;
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
