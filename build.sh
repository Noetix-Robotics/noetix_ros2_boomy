#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")"

build_type=Debug
clean=0
build_requested=0

usage() {
    echo "usage: $0 [-c] [-r|-d]" >&2
    echo "  -c  clean build/install/log and exit unless -r or -d is also given" >&2
    echo "  -r  Release build (no clean)" >&2
    echo "  -d  Debug build (no clean, default)" >&2
}

while getopts ":crdh" opt; do
    case "$opt" in
        c) clean=1 ;;
        r) build_type=Release; build_requested=1 ;;
        d) build_type=Debug; build_requested=1 ;;
        h) usage; exit 0 ;;
        *) usage; exit 2 ;;
    esac
done

if (( clean )); then
    rm -rf build install log
    if (( ! build_requested )); then
        exit 0
    fi
fi

ros2_setup="${ROS2_SETUP:-/opt/ros/humble/setup.bash}"
if [[ ! -f "$ros2_setup" ]]; then
    echo "error: ROS 2 setup not found: $ros2_setup" >&2
    echo "set ROS2_SETUP to the ROS 2 setup.bash path" >&2
    exit 1
fi

set +u
# shellcheck source=/dev/null
source "$ros2_setup"
set -u

export PATH="/usr/bin:/bin:$PATH"

colcon build \
    --packages-select boomy_interaction boomy_motion boomy_ros2_examples \
    --cmake-args "-DCMAKE_BUILD_TYPE=$build_type" "-DPython3_EXECUTABLE=/usr/bin/python3" -Wno-dev
