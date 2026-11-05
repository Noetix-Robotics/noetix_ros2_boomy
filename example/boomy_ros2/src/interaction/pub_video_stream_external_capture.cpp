#include "boomy_interaction/msg/video_stream.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/video_stream_external_capture";
    using T                 = boomy_interaction::msg::VideoStream;
    T sample;
    boomy_interaction::msg::Header header;
    header.message_id   = 1001;
    header.timestamp_us = 1710000000000000ULL;
    header.sn           = "BOOMY-SDK-SAMPLE";
    sample.header       = header;
    sample.timestamp_us = 1710000000000000ULL;
    sample.format       = 0;
    sample.width        = 640;
    sample.height       = 480;
    sample.fps          = 30;
    sample.video_data.assign(32, 0x5a);
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
