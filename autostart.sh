
#!/bin/bash

# Function to check if an application is already running
is_running() {
    pgrep "$1" > /dev/null 2>&1
}

is_running ~/.screenlayout/main.sh || ~/.screenlayout/main.sh &
is_running nitrogen || nitrogen --restore &
is_running dwmblocks || dwmblocks &
is_running nm-applet || nm-applet &
is_running volumeicon || volumeicon &
# for laptop users only!
# is_running cbatticon || cbatticon
is_running conky || conky -c ~/.config/conky/dwm/conky.conf &
is_running udiskie || udiskie &
is_running xclip || xclip &
is_running easyeffects || easyeffects &
is_running solaar || solaar &
is_running sxhkd || sxhkd -c ~/.config/dwm/sxhkdrc &
# cd ~
