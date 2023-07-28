#!/bin/bash
echo " $(curl -Ss 'https://wttr.in/Wetter(Ruhr)?x&T&Q' | cut -c 16- | head -2 | xargs echo) "
