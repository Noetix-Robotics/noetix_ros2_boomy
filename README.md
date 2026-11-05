# noetix_ros2_boomy

**ROS 2 interface definitions and examples for the Boomy robot.**

![ROS 2](https://img.shields.io/badge/ROS%202-Humble-22314E?logo=ros&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%E2%89%A53.14-064F8C?logo=cmake&logoColor=white)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-BSD--3--Clause-blue)

---

## Overview

This repository describes the Boomy robot's two communication domains as ROS 2
interfaces, and ships a runnable publish/subscribe example for every topic.

- **`boomy_interaction`** — interaction domain: audio streaming, audio volume,
  audio control, video streaming, video control, interaction state and errors,
  and general configuration.
- **`boomy_motion`** — motion domain: motion control commands, mode switching,
  motor commands, and robot status (IMU / joystick / BMS / motor states) plus
  robot information.

The message set is kept layout-compatible with the robot's underlying DDS
types, so a deployment can speak either ROS 2 or plain DDS with identical
payloads.

## Contents

| Path | Description |
|---|---|
| `interface/boomy_interaction` | ROS 2 messages for the interaction domain (10 messages) |
| `interface/boomy_motion` | ROS 2 messages for the motion domain (14 messages present, 16 intended) |
| `example/boomy_ros2` | ROS 2 (rclcpp) publish/subscribe examples — 44 executables |
| `build.sh` | Top-level `colcon` build script |
| `VERSION` | SDK version (`1.0.0`) |

## Repository layout

```text
noetix_ros2_boomy/
├── build.sh                        # colcon build script
├── VERSION                         # SDK version
├── LICENSE                         # BSD 3-Clause
├── .clang-format                   # C++ formatting (LLVM based, 4 spaces)
├── .cmake-format.json              # CMake formatting
├── interface/
│   ├── boomy_interaction/          # 10 messages + CMakeLists.txt + package.xml
│   │   ├── msg/
│   │   └── CMakeLists.txt
│   └── boomy_motion/               # 14 messages + CMakeLists.txt + package.xml
│       ├── msg/
│       ├── README.md
│       └── CMakeLists.txt
└── example/
    └── boomy_ros2/                 # 44 pub/sub executables
        ├── CMakeLists.txt
        ├── package.xml
        └── src/
            ├── common/ros2_example_common.hpp
            ├── interaction/        # 36 executables (18 topics × pub/sub)
            └── motion/             # 8 executables (4 topics × pub/sub)
```

Build outputs (`build/`, `install/`, `log/`) are ignored by `.gitignore`.

## Requirements

| Requirement | Notes |
|---|---|
| ROS 2 **Humble** | Default `/opt/ros/humble`; override with `ROS2_SETUP` |
| CMake ≥ 3.14 | |
| C++17 compiler | |
| Python 3 at `/usr/bin/python3` | The ROS 2 Python packages on the target are installed for that interpreter |
| `colcon` | Ships with ROS 2 |

## Build

```bash
./build.sh
source install/setup.bash
```

`build.sh` sources `/opt/ros/humble/setup.bash` by default. Point it elsewhere
when ROS 2 is installed in a different location:

```bash
export ROS2_SETUP=/path/to/ros2/install/setup.bash
./build.sh
```

It builds exactly these packages with `colcon`:

```text
boomy_interaction  boomy_motion  boomy_ros2_examples
```

The build pins `Python3_EXECUTABLE=/usr/bin/python3` because the ROS 2 Python
packages on the target are installed for that interpreter.

### Options

```text
-c  clean build/install/log and exit; with -r/-d, clean then build
-r  Release build
-d  Debug build (default)
```

| Command | Effect |
|---|---|
| `./build.sh` | Debug build (default), no clean |
| `./build.sh -r` | Release build, no clean |
| `./build.sh -c` | Clean `build/ install/ log/` only |
| `./build.sh -c -r` | Clean, then Release build |

## Interface packages

### `boomy_interaction` (10 messages)

| Message | Fields | Notes |
|---|---|---|
| `Header` | `uint64 message_id`, `uint64 timestamp_us`, `string sn` | Shared header |
| `InteractionControl` | `Header header`, `int32 type`, `bool need_audio_response` | type: `0` TO_WAKEUP, `1` TO_SLEEP, `2` TO_RESET |
| `InteractionStatus` | `Header header`, `int32 value`, `int32 reason` | value: `0` READY, `1` SLEEPED, `2` WAKEUPED, `3` EXIT |
| `InteractionError` | `Header header`, `int32 code`, `string message` | |
| `CommonConfig` | `Header header`, `string common_config` | |
| `AudioStreamFrame` | `Header header`, `uint64 timestamp_us`, `uint32 channels`, `uint32 sample_rate`, `uint32 format`, `uint32 duration_ms`, `int16[] audio_data` | |
| `AudioVolume` | `Header header`, `int32 value` | |
| `AudioControl` | `Header header`, `int32 type` | type: `0` PAUSE_CAPTURE, `1` RESUME_CAPTURE, `2` PAUSE_PLAYBACK, `3` RESUME_PLAYBACK |
| `VideoStream` | `Header header`, `uint64 timestamp_us`, `uint32 format`, `uint32 width`, `uint32 height`, `uint32 fps`, `uint8[] video_data` | |
| `VideoControl` | `Header header`, `int32 type` | type: `0` PAUSE_CAPTURE, `1` RESUME_CAPTURE |

`InteractionStatus.reason` constants: `0` INTERACTION_LAUNCH, `1` CMD_RESET,
`2` AUDIO_WAKEUPED, `3` CMD_WAKEUPED, `4` AUDIO_SLEEPED, `5` CMD_SLEEPED,
`6` TIMEOUT_SLEEPED, `7` ERROR_SLEEPED.

### `boomy_motion` (16 messages intended)

Motion messages carry no shared `Header` — the underlying DDS types did not
define one.

| Message | Fields |
|---|---|
| `MotionControlCMD` | `float64[3] axes`, `int32 action`, `uint16 data` |
| `MotionSetMode` | `uint16 mode` |
| `RobotMotorCommand` | `float64 pos`, `float64 vel`, `float64 tau`, `float64 kp`, `float64 kd`, `uint16 motor_id` |
| `RobotMotorCommandArray` | `RobotMotorCommand[] motorcmds`, `int64 timestamp` |
| `RobotIMUData` | `float64[4] ori`, `float64[9] ori_cov`, `float64[3] angular_vel`, `float64[9] angular_vel_cov`, `float64[3] linear_acc`, `float64[9] linear_acc_cov` |
| `RobotJoyData` | `float64[2] axes`, `int32[14] button` |
| `RobotMotorState` | `float64 pos`, `float64 vel`, `float64 tau`, `uint16 motor_id`, `uint16 error`, `int32 temperature` |
| `RobotMotorStateArray` | `RobotMotorState[] motorstates`, `int64 timestamp` |
| `RobotBMSState` | `uint16 battery_temp`, `uint16 battery_alarm`, `uint16 battery_soc`, `uint16 battery_soh` |
| `RobotStatusData` | `RobotIMUData imudata`, `RobotJoyData joydata`, `RobotBMSState bmsdata`, `uint16 workmode`, `RobotMotorStateArray motorstatearray` |
| `RobotVersion` | `string firmware_version`, `RobotSubVersion sub_version` *(see [Known issues](#known-issues))* |
| `RobotSubVersion` | `string bootloader`, `string kernel`, `string rootfs`, `string robot_app`, `string robot_sdk`, `string robot_audio`, `string robot_cloud` *(see [Known issues](#known-issues))* |
| `RobotInfoIMUData` | same IMU arrays as `RobotIMUData`, plus `uint32 imu_status` |
| `RobotInfoMotorState` | `uint32 error`, `float64 temperature` |
| `RobotInfoMotorStateArray` | `RobotInfoMotorState[] motorstates`, `int64 timestamp` |
| `RobotInfoData` | `RobotVersion version`, `RobotBMSState bmsdata`, `RobotInfoIMUData imudata`, `uint16 workmode`, `RobotInfoMotorStateArray motorstatearray` |

> Fixed-size arrays and nested structs are preserved exactly as the robot
> defines them, so the on-the-wire binary layout matches the DDS types.

## Topics

Every topic has both a publisher and a subscriber example (22 topics × 2 = 44
executables). Each example accepts a topic override as its first command-line
argument; the defaults are listed below.

| Domain | Topic | Message |
|---|---|---|
| interaction | `/boomy/interaction_control` | `InteractionControl` |
| interaction | `/boomy/interaction_status` | `InteractionStatus` |
| interaction | `/boomy/interaction_error` | `InteractionError` |
| interaction | `/boomy/common_config` | `CommonConfig` |
| interaction | `/boomy/common_config_set` | `CommonConfig` |
| interaction | `/boomy/common_config_get` | `CommonConfig` |
| interaction | `/boomy/audio_control` | `AudioControl` |
| interaction | `/boomy/audio_volume` | `AudioVolume` |
| interaction | `/boomy/audio_volume_set` | `AudioVolume` |
| interaction | `/boomy/audio_volume_get` | `AudioVolume` |
| interaction | `/boomy/audio_stream_external_capture` | `AudioStreamFrame` |
| interaction | `/boomy/audio_stream_external_playback` | `AudioStreamFrame` |
| interaction | `/boomy/audio_stream_internal_capture` | `AudioStreamFrame` |
| interaction | `/boomy/audio_stream_internal_playback` | `AudioStreamFrame` |
| interaction | `/boomy/video_control` | `VideoControl` |
| interaction | `/boomy/video_stream_external_capture` | `VideoStream` |
| interaction | `/boomy/video_stream_internal_capture` | `VideoStream` |
| interaction | `/boomy/video_stream_capture_desensed` | `VideoStream` |
| motion | `/boomy/motion_control_cmd` | `MotionControlCMD` |
| motion | `/boomy/motion_set_mode` | `MotionSetMode` |
| motion | `/boomy/motor_command` | `RobotMotorCommandArray` |
| motion | `/boomy/robot_status_data` | `RobotStatusData` |

## Examples

Build and source the workspace first:

```bash
./build.sh
source install/setup.bash
```

Publish a single sample message (defaults shown; pass a topic name to override):

```bash
ros2 run boomy_ros2_examples pub_motion_control_cmd
ros2 run boomy_ros2_examples pub_motion_control_cmd /boomy/motion_control_cmd
```

Subscribe (runs until Ctrl+C):

```bash
ros2 run boomy_ros2_examples sub_robot_status_data
ros2 run boomy_ros2_examples sub_robot_status_data /boomy/robot_status_data
```

Inspect an interface definition:

```bash
ros2 interface show boomy_motion/msg/RobotStatusData
ros2 interface show boomy_interaction/msg/AudioStreamFrame
```

Naming rule for the 44 executables in `boomy_ros2_examples`: `pub_<topic>` and
`sub_<topic>` for every row of the topic table above.

## Known issues

- **`interface/boomy_motion/msg/RobotVersion.msg` and
  `interface/boomy_motion/msg/RobotSubVersion.msg` are missing.** `RobotInfoData.msg`
  references `RobotVersion`, and `interface/boomy_motion/README.md` lists both,
  but they are absent from the repository and from the `MSG_FILES` list in
  `interface/boomy_motion/CMakeLists.txt`. As a result `boomy_motion` (and
  therefore the whole workspace) does **not** build until they are restored.
- **License metadata is inconsistent.** `LICENSE` is BSD 3-Clause
  (Copyright © 2025 Noetix Robotis), but `boomy_interaction` and `boomy_motion`
  declare `<license>Proprietary</license>` while `boomy_ros2_examples` declares
  `Apache-2.0`. These should be aligned with the top-level `LICENSE`.
- **Version mismatch.** `VERSION` says `1.0.0`, while every `package.xml` says
  `0.1.0`.

## License

BSD 3-Clause License. See [LICENSE](LICENSE) for the full text.

Copyright (c) 2025, Noetix Robotis.
