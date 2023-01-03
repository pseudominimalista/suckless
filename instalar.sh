#!/bin/sh

# Configurando sessão

doas setup-xorg-base
doas apk add lxdm
doas rc-update add lxdm boot
doas cp .lxdm/lxdm.conf /etc/lxdm/
doas cp .lxdm/dwm.desktop /usr/share/xsessions/
doas cp .lxdm/greeter-gtk3.ui /usr/share/lxdm/themes/Alpine/
doas cp .lxdm/gtk.css /usr/share/lxdm/themes/Alpine/


# Atualizar sistema

doas apk update
doas apk upgrade

# Instalação de dependências e programas

doas apk add curl bash gnupg pass git make gcc g++ libx11-dev libxft-dev \
libxinerama-dev imlib2-dev libxrandr-dev linux-headers argp-standalone g++ \
ncurses dbus-x11 dbus dbus-dev xdg-utils xdg-user-dirs xclip gcr-dev webkit2gtk-dev \
xprop alsa-utils udisks2 libgit2-dev xbacklight xset xsetroot setxkbmap man-db \
xf86-input-synaptics xf86-video-intel p7zip dunst zathura xrdb cmus \
zathura-pdf-mupdf ffmpeg font-noto font-noto-emoji font-noto-cjk  &&

# Configuração de serviços

doas rc-update add dbus

# Compilar programas

doas make clean install --directory=src/dwm/			;
doas make clean install --directory=src/dmenu/			;
doas make clean install --directory=src/slstatus/		;
doas make clean install --directory=src/st/				;
doas make clean install --directory=src/scroll/			;
doas make clean install --directory=src/slock/			;
doas make clean install --directory=src/bgs/			;
doas make clean install --directory=src/surf/			;		
doas make clean install --directory=src/tabbed/			;
doas make clean install --directory=src/farbfeld/		;
doas make clean install --directory=src/xscreenshot/	;
doas make clean install --directory=src/lel/			;
doas make clean install --directory=src/sxiv/			;
doas make clean install --directory=src/sent/			;
doas make clean install --directory=src/catpoint/		;
doas make clean install --directory=src/saait/			;
doas make clean install --directory=src/stagit/			;
doas make clean install --directory=src/quark/			;

# Cópia de arquivos

cp .profile ~/
cp .Xresources ~/
cp .wp ~/
cp -r .dwm/ ~/
cp -r .config/ ~/
cp -r .surf/ ~/
doas cp .repositories /etc/apk/repositories
doas cp .desktop/* /usr/share/applications 
doas cp .scripts/* /usr/local/bin/
doas cp -r .bin /usr/local/bin/
doas cp -r .cmus /usr/share/cmus
doas chmod +x /usr/local/bin/*

# Reiniciar o computador

doas reboot
