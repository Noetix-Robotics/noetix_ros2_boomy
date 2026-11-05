#include "boomy_interaction/msg/video_stream.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/video_stream_capture_desensed";
    using T                 = boomy_interaction::msg::VideoStream;
    return ros2_example::RunSub<T>(argc, argv, topic);
}
