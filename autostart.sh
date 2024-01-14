#!/bin/sh

# Function to check if an application is already running
is_running() {
    pgrep "$1" > /dev/null 2>&1
}

is_running ~/.screenlayout/main.sh || ~/.screenlayout/main.sh &
is_running nitrogen || nitrogen --restore &
is_running dwmblocks || dwmblocks &
is_running nm-applet || nm-applet &
<<<<<<< HEAD
=======
is_running volumeicon || volumeicon &
>>>>>>> refs/remotes/origin/main
is_running udiskie || udiskie &
is_running xclip || xclip &
is_running easyeffects || easyeffects &
is_running solaar || solaar &
<<<<<<< HEAD
/usr/bin/emacs --daemon &
=======

# No more caps lock
setxkbmap -option caps:none
>>>>>>> refs/remotes/origin/main
