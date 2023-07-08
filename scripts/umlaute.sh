#! /bin/bash

umlaute="ä\nö\nü\nß\n"
dmenu="rofi -dmenu"

sel="$(printf $umlaute | $dmenu)"
sleep 0.2s
xdotool type $sel
