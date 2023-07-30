#!/bin/sh

awk '/MemTotal/ {total=$2} /MemAvailable/ {available=$2} END {printf("%.2f GB\n", (total - available) / (1024*1024))}' /proc/meminfo
