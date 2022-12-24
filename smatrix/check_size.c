/*  This file is part of smatrix.                                           */
/*                                                                          */
/*  Smatrix is free software: you can redistribute it and/or modify it      */
/*  under the terms of the GNU General Public License as published by       */
/*  the Free Software Foundation, either version 2 of the License, or       */
/*  (at your option) any later version.                                     */
/*                                                                          */
/*  Smatrix is distributed in the hope that it will be useful, but WITHOUT  */
/*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY      */
/*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public         */
/*  License for more details.                                               */
/*                                                                          */
/*  You should have received a copy of the GNU General Public License       */
/*  along with smatrix. If not, see <https://www.gnu.org/licenses/>.        */

/*  The purpose of this program is to cycle through the entire linked-list  */
/*  of drops and move each forward by some amount. Right now that amount is */
/*  one, but by configuration of the program on start we hope to be able    */
/*  to make changes and adjustments to this function for improved and       */
/*  extended functionality.                                                 */

int
check_size(struct winsize *terminal_dimensions)
{
    int old_width, old_height;

    old_width = terminal_dimensions->ws_col;
    old_height = terminal_dimensions->ws_row;

    ioctl(0, TIOCGWINSZ, terminal_dimensions);

    /*	If I did this right, this should return 1 if these values change,	*/
	/*	and zero otherwise, while updating them in either case.				*/

    if 	 ( (old_height == terminal_dimensions->ws_row )
   		&& (old_width  == terminal_dimensions->ws_col ) )
	{
    	return 0;
	} else {
		return 1;
	}
}

