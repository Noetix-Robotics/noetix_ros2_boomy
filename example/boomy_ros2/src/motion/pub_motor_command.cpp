#include "boomy_motion/msg/robot_motor_command_array.hpp"
#include "common/ros2_example_common.hpp"

#include <chrono>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/motor_command";

    using T = boomy_motion::msg::RobotMotorCommandArray;

    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("boomy_ros2_pub");

    // Configure QoS
    rclcpp::QoS qos(rclcpp::KeepLast(1));

    qos.reliable()
       .lifespan(std::chrono::milliseconds(2))
       .deadline(std::chrono::milliseconds(2))
       .liveliness(RMW_QOS_POLICY_LIVELINESS_AUTOMATIC)
       .liveliness_lease_duration(std::chrono::milliseconds(500));

    auto publisher = node->create_publisher<T>(topic, qos);

    T sample;
    sample.motorcmds.reserve(21);

    for (uint16_t i = 0; i < 21; ++i) {
        boomy_motion::msg::RobotMotorCommand command;

        command.pos      = 0.0;
        command.vel      = 0.0;
        command.tau      = 0.0;
        command.kp       = 2.0;
        command.kd       = 0.5;
        command.motor_id = i;

        sample.motorcmds.push_back(command);
    }

    sample.timestamp = 1710000000000000LL;

    rclcpp::sleep_for(std::chrono::seconds(1));

    publisher->publish(sample);

    RCLCPP_INFO(node->get_logger(), "published on %s", topic.c_str());

    rclcpp::shutdown();
    return 0;
}
