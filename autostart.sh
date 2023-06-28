#!/bin/bash

~/.screenlayout/main.sh &
nitrogen --restore &
dwmblocks &
nm-applet &
volumeicon &
# for laptop users only!
# cbatticon
conky -c ~/.config/conky/dwm/conky.conf &
udiskie &
xclip &
easyeffects &
solaar &
sxhkd -c ~/.config/dwm/sxhkdrc &
