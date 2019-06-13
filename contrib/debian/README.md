
Debian
====================
This directory contains files used to package idchaind/idchain-qt
for Debian-based Linux systems. If you compile idchaind/idchain-qt yourself, there are some useful files here.

## idchain: URI support ##


idchain-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install idchain-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your idchainqt binary to `/usr/bin`
and the `../../share/pixmaps/idchain128.png` to `/usr/share/pixmaps`

idchain-qt.protocol (KDE)
