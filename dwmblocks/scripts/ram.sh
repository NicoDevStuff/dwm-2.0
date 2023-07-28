#!/bin/bash
echo "$(awk '/MemTotal/ {total=$2} /MemAvailable/ {available=$2} END {printf("%.2f%%\n", (total - available) / total * 100)}' /proc/meminfo)"
