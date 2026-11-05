#include "boomy_interaction/msg/audio_stream_frame.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/audio_stream_internal_playback";
    using T                 = boomy_interaction::msg::AudioStreamFrame;
    T sample;
    boomy_interaction::msg::Header header;
    header.message_id   = 1001;
    header.timestamp_us = 1710000000000000ULL;
    header.sn           = "BOOMY-SDK-SAMPLE";
    sample.header       = header;
    sample.timestamp_us = 1710000000000000ULL;
    sample.channels     = 1;
    sample.sample_rate  = 16000;
    sample.format       = 1;
    sample.duration_ms  = 20;
    sample.audio_data.resize(320);
    for (size_t i = 0; i < sample.audio_data.size(); ++i) {
        sample.audio_data[i] = static_cast<int16_t>((i % 32) * 128 - 2048);
    }
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
