
Debian
====================
This directory contains files used to package idccd/idcc-qt
for Debian-based Linux systems. If you compile idccd/idcc-qt yourself, there are some useful files here.

## idcc: URI support ##


idcc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install idcc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your idccqt binary to `/usr/bin`
and the `../../share/pixmaps/idcc128.png` to `/usr/share/pixmaps`

idcc-qt.protocol (KDE)
