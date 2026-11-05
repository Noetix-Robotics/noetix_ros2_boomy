#pragma once

#include <rclcpp/rclcpp.hpp>

#include <chrono>
#include <memory>
#include <string>

namespace ros2_example {

template <typename T>
int RunPub(int argc, char** argv, const std::string& topic, const T& sample) {
    rclcpp::init(argc, argv);
    auto node      = std::make_shared<rclcpp::Node>("boomy_ros2_pub");
    auto publisher = node->create_publisher<T>(topic, 10);

    rclcpp::sleep_for(std::chrono::seconds(1));
    publisher->publish(sample);
    RCLCPP_INFO(node->get_logger(), "published on %s", topic.c_str());

    rclcpp::shutdown();
    return 0;
}

template <typename T>
int RunSub(int argc, char** argv, const std::string& topic) {
    rclcpp::init(argc, argv);
    auto node         = std::make_shared<rclcpp::Node>("boomy_ros2_sub");
    auto subscription = node->create_subscription<T>(
        topic,
        10,
        [node, topic](std::shared_ptr<const T> message) {
            (void)message;
            RCLCPP_INFO(node->get_logger(), "received on %s", topic.c_str());
        });
    (void)subscription;

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

} // namespace ros2_example
