#!/bin/sh

# Instalação de dependências e programas
doas apk add lightdm bash gnupg pass git make gcc g++ libx11-dev libxft-dev \
libxinerama-dev libjpeg-turbo-dev libpng-dev giflib-dev libexif-dev imlib2-dev \
libxrandr-dev linux-headers argp-standalone ncurses dbus-x11 xdg-utils xclip dunst \
gcr-dev webkit2gtk-dev xprop alsa-utils vim udisks2 libgit2-dev xbacklight \
xset xsetroot setxkbmap dunst zathura zathura-pdf-mupdf &&

# Configurando xorg
doas setup-xorg-base

# Habilitando LightDM
doas rc-update add lightdm

# Compilar programas (Ainda não tá pronto)
doas make clean install --directory=dmenu/		;
doas make clean install --directory=dwm/		;
doas make clean install --directory=dwmblocks/	;
doas make clean install --directory=sent/		;
doas make clean install --directory=st/			;
doas make clean install --directory=bgs/		;
doas make clean install --directory=farbfeld/	;
doas make clean install --directory=smatrix/	;
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
doas cp .todo /usr/local/bin/todo
doas cp .dfm /usr/local/bin/dfm
doas cp dwm.desktop /usr/share/xsessions 
doas cp zathura.desktop /usr/share/applications
doas cp lightdm.conf /etc/lightdm/ 
chmod +x ~/.dwm/autostart.sh

# Reiniciar o computador
doas reboot
