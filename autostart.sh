#!/bin/sh

is_running() {
    pgrep "$1" > /dev/null 2>&1
}

~/.screenlayout/main.sh &
nitrogen --restore &

is_running dwmblocks || dwmblocks &
is_running nm-applet || nm-applet &
is_running volumeicon || volumeicon &
is_running udiskie || udiskie &
is_running xclip || xclip &
is_running easyeffects || easyeffects &
is_running solaar || solaar &
