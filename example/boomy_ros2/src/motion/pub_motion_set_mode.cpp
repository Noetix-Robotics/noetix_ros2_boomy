#include "boomy_motion/msg/motion_set_mode.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motion_set_mode";

    using T = boomy_motion::msg::MotionSetMode;

    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("boomy_ros2_pub");

    rclcpp::QoS qos(rclcpp::QoSInitialization::from_rmw(rmw_qos_profile_default));
    qos.reliable()
       .transient_local();

    auto publisher = node->create_publisher<T>(topic, qos);

    T sample;
    sample.mode = 1;

    rclcpp::sleep_for(std::chrono::seconds(1));
    publisher->publish(sample);

    RCLCPP_INFO(node->get_logger(), "published on %s", topic.c_str());

    rclcpp::shutdown();
    return 0;
}
