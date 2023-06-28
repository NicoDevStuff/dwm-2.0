#!/bin/bash

delim="|"
status=""
echo "$$" > ~/.config/dwm/pid

add_element() {
	status="$status $1 $delim"
}

capslock() {
    caps_state=$(xset q | grep "Caps Lock:" | awk '{print $4}')
    
    if [ "$caps_state" == "on" ]; then
		add_element "🟥🟥🟥 CAPS 🟥🟥🟥"
    fi
}

volume () {
	if [ $(pamixer --get-mute) = "true" ]; then
		echo " 🔇 "
	else 
		echo " 🔊 $(pamixer --get-volume)% "
	fi
}
# volume
add_element "$(volume)"
# cpu usage 
add_element "💻 $(echo ""$[100-$(vmstat 1 2|tail -1|awk '{print $15}')]"% ")"
# cpu heat 
add_element "🔥 $(echo "$(sensors | grep "Package id 0:" | tr -d '+' | awk '{print $4}')")"
# memory usage
add_element "🧠 $(echo "$(awk '/MemTotal/ {total=$2} /MemAvailable/ {available=$2} END {printf("%.2f%%\n", (total - available) / total * 100)}' /proc/meminfo)")"
# date
add_element "📆 $(date +%F)"
# time
add_element "🕒 $(date +%H:%M)"

reload_script() {
    # Perform any necessary cleanup or pre-reload tasks here
    
    # Reload the script by executing it again with the same arguments
    exec "$0" "$@"
}

# Register a signal handler to listen for the reload signal (SIGUSR1)
trap reload_script SIGUSR1

while true ; do
	capslock
	xsetroot -name "$status"
	
	# Sleep for a very short duration (0.1 seconds) to allow signals to be caught
	# This effectively reduces the delay between iterations
	sleep 0.1s
done

