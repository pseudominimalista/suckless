#!/bin/sh
xsetroot -bg \#1e1e2e -fg \#1e1e2e -gray; bgs ~/.wp; xrdb -merge ~/.Xresources
/usr/local/bin/dwmblocks && xset led named "Scroll Lock"

