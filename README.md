# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


## Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## My Patches

This is in the order that I patched everything:

- [shiftview](https://lists.suckless.org/dev/1104/7590.html)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [systray](https://dwm.suckless.org/patches/systray/)
- [staticstatus](https://dwm.suckless.org/patches/staticstatus/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
- [cycle layout](https://dwm.suckless.org/patches/cyclelayouts/)

## Media keys

Here is a helpful [link](https://gist.github.com/palopezv/efd34059af6126ad970940bcc6a90f2e)

**NOTE** (I had to change "0" to "@DEFAULT_SINK@")
