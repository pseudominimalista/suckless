#!/bin/sh

# Configurando sessão 
doas setup-xorg-base
doas apk add lxdm
doas rc-update add lxdm boot
doas cp .lxdm.conf /etc/lxdm/lxdm.conf

# Instalação de dependências e programas
doas apk add bash gnupg pass git make gcc g++ libx11-dev libxft-dev \
libxinerama-dev libjpeg-turbo-dev libpng-dev giflib-dev libexif-dev imlib2-dev \
libxrandr-dev linux-headers argp-standalone ncurses dbus-x11 xdg-utils xclip dunst \
gcr-dev webkit2gtk-dev xprop alsa-utils vim udisks2 udiskie libgit2-dev xbacklight \
xset xsetroot setxkbmap dunst zathura zathura-pdf-mupdf ffmpeg font-noto fzf &&

# Compilar programas 
doas make clean install --directory=dmenu/		;
doas make clean install --directory=dwm/		;
doas make clean install --directory=dwmblocks/	;
doas make clean install --directory=sent/		;
doas make clean install --directory=st/			;
doas make clean install --directory=bgs/		;
doas make clean install --directory=farbfeld/	;
doas make clean install --directory=stagit      ;
doas make clean install --directory=sxiv/		;
doas make clean install --directory=slock/		;
doas make clean install --directory=quark/		;
doas make clean install --directory=surf/		;	

# Copia de arquivos
mkdir ~/.dwm 
cp -r .config/ ~/
cp -r .surf/ ~/
cp .autostart.sh ~/.dwm/autostart.sh
cp .Xresources ~/
cp .wp ~/
doas cp .web /usr/local/bin/web
doas cp .todo /usr/local/bin/todo
doas cp .dfm /usr/local/bin/dfm
doas cp .desktop/sxiv.desktop /usr/share/applications
doas cp .desktop/ffplay.desktop /usr/share/applications
doas cp .desktop/zathura.desktop /usr/share/applications
doas cp .desktop/dwm.desktop /usr/share/xsessions
chmod +x ~/.dwm/autostart.sh
