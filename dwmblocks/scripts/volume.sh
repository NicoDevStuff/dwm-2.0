#!/bin/sh
if [ $(pamixer --get-mute) = "true" ]; then
	echo "🔇"
else 
	volume=$(pamixer --get-volume)

	if [ "$volume" -eq 0 ]; then
		echo "🔈 $volume%"
	elif [ "$volume" -lt 50 ]; then
		echo "🔉 $volume%"
	else
		echo "🔊 $volume%"
	fi
fi
