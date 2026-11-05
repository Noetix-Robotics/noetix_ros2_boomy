# boomy_motion

ROS 2 interface package for the Boomy motion domain.

```text
boomy_motion/msg/<Name>
```

## Layout

```text
boomy_motion/
  msg/MotionControlCMD.msg, MotionSetMode.msg
  msg/RobotIMUData.msg, RobotJoyData.msg, RobotMotorState.msg,
      RobotBMSState.msg, RobotMotorStateArray.msg, RobotStatusData.msg
  msg/RobotMotorCommand.msg, RobotMotorCommandArray.msg
```

## DDS mapping

| DDS type | ROS 2 type |
|---|---|
| `RobotControlCmd::ControlCmd` | `boomy_motion/msg/MotionControlCMD` |
| `RobotSetMode::SetMode` | `boomy_motion/msg/MotionSetMode` |
| `RobotStatus::ImuData` | `boomy_motion/msg/RobotIMUData` |
| `RobotStatus::JoyData` | `boomy_motion/msg/RobotJoyData` |
| `RobotStatus::MotorState` | `boomy_motion/msg/RobotMotorState` |
| `RobotStatus::BmsState` | `boomy_motion/msg/RobotBMSState` |
| `RobotStatus::MotorStateArray` | `boomy_motion/msg/RobotMotorStateArray` |
| `RobotStatus::StatusData` | `boomy_motion/msg/RobotStatusData` |
| `RobotMotorCmd::MotorCmdArray` | `boomy_motion/msg/RobotMotorCommandArray` |

DDS fixed arrays and nested structs are preserved. Motion messages have no
shared header; the DDS types did not define one.

## Deployment modes

The deployment chooses exactly one schema/topic set; there is no runtime dual
publish or subscribe.

```yaml
schema_mode: ros2      # boomy_motion + ROS 2-derived DDS
# schema_mode: legacy  # original RobotControlCmd / RobotSetMode / RobotStatus
```


## Build

```bash
cd <noetix_ros2_boomy>
export ROS2_SETUP=/path/to/ros2/install/setup.bash
source "$ROS2_SETUP"
colcon build --packages-select boomy_motion
source install/setup.bash
ros2 interface show boomy_motion/msg/RobotStatusData
```
