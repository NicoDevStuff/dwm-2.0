#!/bin/sh

# Read the PID from the file
pid=$(cat ~/.config/dwm/pid)

# Send the SIGUSR1 signal to reload the script
kill -SIGUSR1 "$pid"
