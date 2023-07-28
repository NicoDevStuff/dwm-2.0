#!/bin/bash
if [ $(pamixer --get-mute) = "true" ]; then
	echo " 🔇 "
else 
	echo " 🔊 $(pamixer --get-volume)%"
fi
