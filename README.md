# backlight

A very simple program to control backlight (tested on my Lenovo carbon x4 and a HP elitebook).
I've developped it because i3 (window manager) was not controlling backlight and I wanted a very simple solution.

## Use
Increment brightness :
backlight_mod ++

Decrement brightness :
backlight_mod --

## Installation
1. Download the code
2. run : make
3. Move the executable wherever you want OR run : sudo make install --> It will install it in /usr/bin

## i3 config
Add those lines in you i3 config file :
```
# Screen brightness controls
bindsym XF86MonBrightnessUp exec --no-startup-id backlight_mod ++ # increase screen brightness
bindsym XF86MonBrightnessDown exec --no-startup-id backlight_mod -- # decrease screen brightness
```

## Planned improvements (not to soon, I have a lot of projects)
  - Being able to go to min/max brightness
  - Being able to set a relative value in percent
