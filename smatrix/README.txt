smatrix is a simple cmatrix clone, written in pure C.

It was designed to be efficient, simple, and minimal. In two of these
things, it was successful.

ATM, smatrix can be made with the command:

	make

Run with

	make run

cleaned with

	make clean

And installed manually with

	make && sudo cp smatrix /usr/local/bin/

smatrix has several advantages over cmatrix. It uses ~50% fewer system
resources, integrates more cleanly with the terminal window, respects terminal
and text color/transparency, and in some cases is safer to resize.

Copyright 2022 Ryan Raymond

     This program is free software: you can redistribute it and/or modify it
     under the terms of the GNU General Public License as published by the
     Free Software Foundation, either version 3 of the License, or (at your
     option) any later version.

     This program is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program. If not, see
     <https://www.gnu.org/licenses/>. 
