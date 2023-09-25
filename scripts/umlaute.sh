#!/bin/sh

umlaute="ä\nÄ\nö\nÖ\nü\nÜ\nß\nЯ"
dmenu="rofi -dmenu"

sel="$(printf $umlaute | $dmenu)"
sleep 0.2s
xdotool type $sel
