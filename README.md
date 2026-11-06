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
  motor commands, and robot status (IMU / joystick / BMS / motor states).

The message set is kept layout-compatible with the robot's underlying DDS
types, so a deployment can speak either ROS 2 or plain DDS with identical
payloads.

## Contents

| Path | Description |
|---|---|
| `interface/boomy_interaction` | ROS 2 messages for the interaction domain (10 messages) |
| `interface/boomy_motion` | ROS 2 messages for the motion domain (10 messages) |
| `example/boomy_ros2` | ROS 2 (rclcpp) publish/subscribe examples — 44 executables |
| `config/dds.xml` | CycloneDDS configuration used by the examples at runtime |
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
├── config/
│   └── dds.xml                     # CycloneDDS configuration (peers, transport)
├── interface/
│   ├── boomy_interaction/          # 10 messages + CMakeLists.txt + package.xml
│   │   ├── msg/
│   │   └── CMakeLists.txt
│   └── boomy_motion/               # 10 messages + CMakeLists.txt + package.xml
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

## Environment setup

Install ROS 2 Humble and the CycloneDDS RMW (Ubuntu 22.04):

```bash
# Add the ROS 2 apt repository
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
     -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" \
     | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# ROS 2 base + build tools + CycloneDDS RMW
sudo apt update
sudo apt install -y ros-humble-ros-base ros-humble-rmw-cyclonedds-cpp \
    python3-colcon-common-extensions python3-rosdep
sudo rosdep init 2>/dev/null; rosdep update
```

Add the ROS 2 environment and the DDS RMW to your shell profile:

```bash
echo 'source /opt/ros/humble/setup.bash'              >> ~/.bashrc
echo 'export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp'   >> ~/.bashrc
source /opt/ros/humble/setup.bash
```

After building, also source the workspace so the message types are found:

```bash
echo 'source /path/to/noetix_ros2_boomy/install/setup.bash' >> ~/.bashrc
```

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

### Stream formats

Only one format is currently supported per stream direction.

**Audio streams (`AudioStreamFrame`)** — `format` is `2` (little-endian,
16-bit signed PCM):

| Direction | Topics | `channels` | `sample_rate` | `format` |
|---|---|---|---|---|
| Capture (input) | `/boomy/audio_stream_external_capture`, `/boomy/audio_stream_internal_capture` | 8 | 16000 | 2 |
| Playback (output) | `/boomy/audio_stream_external_playback`, `/boomy/audio_stream_internal_playback` | 2 | 16000 | 2 |

**Video streams (`VideoStream`)** — only the **YUYV** format is supported, so
`video_data` always carries YUYV frames; `width`, `height` and `fps` describe
the frame layout.

### `boomy_motion` (10 messages)

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

## Motion control reference

### `MotionSetMode.mode` values

`MotionSetMode` selects how the robot is driven:

| Value | Mode | Control interface |
|---|---|---|
| 1 | **High mode** | The robot runs its factory algorithm and action models; command it with `MotionControlCMD` |
| 2 | **Low mode** | The factory algorithms are bypassed; drive all joint motors directly with `RobotMotorCommandArray` |

### `MotionControlCMD.action` values

`MotionControlCMD` carries three axes (`float64[3] axes`), the `action` below,
and a `uint16 data` field.

Each axis is normalised to the range `[-1, 1]`:

| Index | Meaning | Positive direction |
|---|---|---|
| `axes[0]` | Turning | `> 0` turns left |
| `axes[1]` | Forward / backward | `> 0` moves forward |
| `axes[2]` | Lateral translation | `> 0` strafes left |

The `action` field selects the mode or the factory-preset action to run.

| Value | Name | Description |
|---|---|---|
| 0 | `WALK` | Walking Mode (half-body walking) |
| 1 | `SWING` | Factory-preset action: Wave |
| 2 | `SHAKE` | Factory-preset action: Handshake |
| 3 | `CHEER` | Factory-preset action: Cheer |
| 4 | `FULLWALK` | Full-body walking |
| 5 | `START` | Enable / Disable |
| 6 | `SWITCH` | Preparation Mode |
| 7 | `STARTTEACH` | Start teaching |
| 8 | `SAVETEACH` | Save teaching |
| 9 | `ENDTEACH` | End teaching |
| 10 | `PLAYTEACH` | Play demonstration |
| 11 | `DANCE0` | Dance 1 mode (What Is Love) |
| 12 | `FALLTOSTAND` | Stand up |
| 13 | `STANDTOFALL` | Stow |
| 14 | `DANCE1` | Dance 2 mode (Jueshi) |
| 15 | `DANCE2` | Dance 3 mode (Gee) |
| 16 | `ZHOUJI` | Elbow strike |
| 17 | `DEFAULT` | Null mode (empty command) |

### Action commands are edge-triggered

Action-type commands are **events** and must be sent only once — not
continuously inside the control loop. The robot runs its control function in a
periodic loop, so re-publishing a one-shot action such as `PLAYTEACH`
interrupts the action before it finishes and makes the robot appear stuck and
unresponsive.

Publish `DEFAULT` (17) on every subsequent loop iteration instead. Note that
`MotionControlCMD.msg` defines **no named constants** — use the values from the
table above:

```cpp
#include "boomy_motion/msg/motion_control_cmd.hpp"

using MotionControlCMD = boomy_motion::msg::MotionControlCMD;

constexpr int32_t kPlayTeach = 10;  // PLAYTEACH
constexpr int32_t kDefault   = 17;  // DEFAULT

auto publisher = node->create_publisher<MotionControlCMD>(
    "/boomy/motion_control_cmd", 10);

MotionControlCMD cmd;
cmd.axes = {0.0, 0.0, 0.0};
cmd.data = 0;

static bool triggered = false;

// Inside the periodic control loop:
if (!triggered) {
    cmd.action = kPlayTeach;  // trigger the demonstration once
    triggered  = true;
} else {
    cmd.action = kDefault;    // empty command; do not re-trigger
}
publisher->publish(cmd);
```

The effect: `PLAYTEACH` starts the demonstration and lets it run to
completion, while the following `DEFAULT` commands no longer interrupt it.

### `START` — enable / disable

Publishing `START` (5) toggles the robot's enabled state. What it does depends
on the current mode read from `RobotStatusData.workmode` on
`/boomy/robot_status_data`:

- `workmode == 30` (Disabled Mode) → publishing `START` puts the robot into enabled mode
- `workmode != 30` → publishing `START` immediately puts the robot into disabled mode

```cpp
MotionControlCMD cmd;
cmd.axes   = {0.0, 0.0, 0.0};
cmd.action = 5;  // START: enables when workmode == 30, otherwise disables
cmd.data   = 0;
publisher->publish(cmd);
```

### Mode state machine

```text
        power-on / motion control start
                    │
                    ▼
  Enable Mode (0)  ⇄──── START (5) ────⇄  Disabled Mode (30)
        │  ▲
   SWITCH (6) │
        ▼  │
  Preparation Mode (1)
        │ WALK (0)
        ▼
  Half-Body Walking Mode (2) ◀───────────────────────┐
        │                                             │
        ├── FULLWALK (4) ──▶ Full-Body Walking Mode (3)
        │                                             │
        ├── Full-body actions ────────────────────────┤
        │   (dances, greeting, handshake,             │ on finish (auto)
        │    cheer, elbow strike)                     │
        │                                             │
        └── Teaching flow ────────────────────────────┘
            STARTTEACH (7) ──▶ PLAYTEACH (10) ─┬─ SAVETEACH (8) ──▶ save
                                                │   (auto-return to walking)
                                                └─ ENDTEACH (9)  ──▶ end
                                                    (manual return to walking)

  standup  (FALLTOSTAND, 12):
      Disabled / lie-down  ──stand-up action flow──▶  Half-Body Walking Mode (2)

  liedown  (STANDTOFALL, 13):
      Half-Body Walking Mode (2)  ──lie-down action flow──▶  Disabled Mode (30)
```

### standup and liedown

Two named transition flows sit on the boundary between disabled and walking
modes:

| Transition | Command | From | To |
|---|---|---|---|
| **standup** | `FALLTOSTAND` (12) | lie-down (Disabled Mode, 30) | Half-Body Walking Mode (2) |
| **liedown** | `STANDTOFALL` (13) | Half-Body Walking Mode (2) | Disabled Mode (30) |

- **standup** — from the lie-down state, the stand-up action flow brings the
  robot into walking mode.
- **liedown** — from walking mode, the lie-down action flow brings the robot
  into disabled mode.

Behaviour notes from the diagram:

- After playing a demonstration (`PLAYTEACH`), you must **manually** return to
  walking mode, otherwise the robot stays in the demonstration's final pose.
- If you do not want to save the demonstrated motion, you must **manually**
  return to walking mode.
- After saving (`SAVETEACH`), the robot returns to walking mode
  **automatically**.
- After a full-body action finishes, the robot returns to half-body walking
  mode **automatically**.

### `RobotStatusData.workmode` values

`RobotStatusData.workmode` reports the robot's current mode:

| Value | Description |
|---|---|
| 0 | Enable Mode |
| 1 | Preparation Mode |
| 2 | Half-Body Walking Mode |
| 3 | Full-Body Walking Mode |
| 5 | Dance Mode 0 |
| 8 | Factory Preset Action: Greeting |
| 9 | Factory Default Action: Handshake |
| 10 | Factory Default Action: Cheer |
| 11 | Start Teaching |
| 12 | End Teaching |
| 13 | Play Demonstration |
| 14 | Save Teaching |
| 23 | Play Demonstration |
| 26 | Protection Mode |
| 27 | Get up from the ground |
| 28 | Get up and fall to the ground |
| 29 | Save Demonstrated Motion |
| 30 | Disabled Mode |
| 31 | Dance Mode 1 |
| 32 | Dance Mode 2 |
| 33 | Elbow Strike Motion |

### Save teaching status sequence

After the application publishes `SAVETEACH` (8) on
`/boomy/motion_control_cmd`, the robot reports three statuses in succession
through `RobotStatusData.workmode`: **Exit Teaching**, then **Save Teaching
1**, then **Save Teaching 2**.

### Protection Mode (workmode 26)

When the robot is under a standing control strategy (walking, teaching,
dancing, etc.), the motion control program continuously monitors IMU attitude
data. If the attitude deviates from the stable standing range and exceeds the
preset threshold, the protection mechanism triggers immediately and forces a
switch to safe mode.

In protection mode:

- All joints enter the disabled state (the motors stop active output).
- The current motion control strategy is terminated.
- Further action commands are blocked from execution.

This mechanism exists to:

- Prevent the robot from continuously outputting control torque during a fall
  or loss of stability.
- Avoid secondary damage caused by uncontrolled swinging of the limbs.
- Reduce potential damage to the device itself and the surrounding
  environment.

Protection logic is a low-level safety mechanism with the **highest
priority**, and it is not affected by upper-layer control commands.

## DDS runtime environment

The examples talk to the robot over CycloneDDS. Configure the DDS environment
before running them:

```bash
export CYCLONEDDS_URI=file:///$(pwd)/config/dds.xml
export ROS_DOMAIN_ID=0
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
```

`config/dds.xml` disables multicast and lists the robot as a peer — replace
`192.168.55.102` in the `<Peer>` entry with the robot's actual address. Use
`ROS_DOMAIN_ID` to isolate the robot from other DDS traffic on the same network.

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

## License

BSD 3-Clause License. See [LICENSE](LICENSE) for the full text.

Copyright (c) 2026, Noetix Robotis.
