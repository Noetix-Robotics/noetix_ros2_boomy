#include "boomy_motion/msg/robot_motor_state.hpp"
#include "boomy_motion/msg/robot_status_data.hpp"
#include "common/ros2_example_common.hpp"

#include <string>

int main(int argc, char** argv) {
    const std::string topic = argc > 1 ? argv[1] : "/boomy/robot_status_data";
    using T                 = boomy_motion::msg::RobotStatusData;
    T sample;
    sample.imudata.ori             = {1.0, 0.0, 0.0, 0.0};
    sample.imudata.ori_cov         = {0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.1};
    sample.imudata.angular_vel     = {0.0, 0.0, 0.0};
    sample.imudata.angular_vel_cov = {0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.1};
    sample.imudata.linear_acc      = {0.0, 0.0, 9.8};
    sample.imudata.linear_acc_cov  = {0.1, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.1};
    sample.joydata.axes            = {0.0, 0.0};
    sample.joydata.button.fill(0);
    sample.joydata.button[0]     = 1;
    sample.bmsdata.battery_temp  = 30;
    sample.bmsdata.battery_alarm = 0;
    sample.bmsdata.battery_soc   = 80;
    sample.bmsdata.battery_soh   = 95;
    boomy_motion::msg::RobotMotorState motor;
    motor.pos         = 0.0;
    motor.vel         = 0.0;
    motor.tau         = 0.0;
    motor.motor_id    = 1;
    motor.error       = 0;
    motor.temperature = 35;
    sample.motorstatearray.motorstates.push_back(motor);
    sample.motorstatearray.timestamp = 1710000000000000LL;
    sample.workmode                  = 0;
    return ros2_example::RunPub<T>(argc, argv, topic, sample);
}
