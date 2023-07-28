#!/bin/sh

dmenu="rofi -dmenu"
layouts="de\nus\n"
sel="$(printf $layouts | rofi -dmenu)"
setxkbmap $sel
