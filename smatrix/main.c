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

#include "main.h"

int
main(int argc, char *argv[])
{
	signal(SIGINT, event_handler);
	
	struct winsize terminal_dimensions;
	terminal_dimensions.ws_row = 1;
	terminal_dimensions.ws_col = 1;


	struct matrix *_matrix;
	_matrix = matrix_new(terminal_dimensions.ws_col,
			  			 terminal_dimensions.ws_row);
	
	slist *first = NULL;
	srand(time(NULL));
	printf("\e[?25l");

	while (1)
	{
		if (check_size(&terminal_dimensions))
		{
		/*	In the event of a change in terminal dimensions, we need to be	*/
		/*	able to make appropriate adjustments. This check allows us to	*/
		/*	do so. The resizing of the matrix is purely cosmetic.			*/
			_matrix = matrix_new(terminal_dimensions.ws_col,
					     	     terminal_dimensions.ws_row);
		}
		spawn(1, 5, &first, terminal_dimensions, 1, 100);
		draw(&first, _matrix, &terminal_dimensions);
		advance(terminal_dimensions, first);
		usleep(50000);
	
	}
	return 1;
}

