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

void
draw(slist **first, struct matrix *_matrix,
	 struct winsize *terminal_dimensions)
{

	int i;
	slist *current, *tmp;
	current = *first;

	while (current != NULL)
	{
		if 	 ( (current->data->position_y < terminal_dimensions->ws_row) 
			&& (current->data->position_x < terminal_dimensions->ws_col) )
		{
		/*	We don't want to immediately delete drops once they are beyond	*/
		/*	the lower border because we need to know their location so we	*/
		/*	can properly erase their tail. Therefore, we need to check that	*/
		/*	Each drop is *not* out of bounds before we attempt to write to	*/
		/*	the framebuffer. Omitting this essential step will cause a		*/
		/*	segmentation fault.												*/

			_matrix->rows[current->data->position_y]
					.cells[current->data->position_x] = current->data->value;
		}

		if 	 ( (current->data->position_y >= current->data->length)
			&& (current->data->position_y - current->data->length
										  < terminal_dimensions->ws_row) )
		{
		/*	If the drop has gone far enough down the display that doing so	*/
		/*	will not write to locations beyond the bounds of the array,		*/
		/*	walk behind each drop and overwrite its furthest trailing cell	*/
		/*	with a space, "erasing" it. This function doesn't actually know */
		/*	what the furthest cell is. All it knows is if it starts at the	*/
		/*	"top" of the matrix and doesn't skip a row, it will not miss	*/
		/*	Any cells.														*/

			_matrix->rows [current->data->position_y - current->data->length]
					.cells[current->data->position_x] = ' ';
		}

		if (current->data->position_y - current->data->length >
			terminal_dimensions->ws_row )
		{
			
			/*	If we have entered this section, that means that the last	*/
			/*	cell on the end of the tail of our current drop has been	*/
			/*	erased. That's to say, at this point the drop is completely	*/
			/*	invisible to the user. If this step is omitted, the program	*/
			/*	will run perfectly for some time. Eventually its framerate	*/
			/*	would suffer, but it would take ages for an appreciable 	*/
			/*	memory leak to accumulate.									*/
			/*		Technically, though, this isn't a leak, because the		*/
			/*	Allocated ram is very much still in use, and the program	*/
			/*	is still acutely aware of its existence. However, this must	*/
			/*	still be resolved to ensure smooth performance.				*/
			/*		Actually removing the linked list was a massive pain.	*/
			/*	I was far too inexperience to take on something like this,	*/
			/*	but now it is finished, and all is well.					*/

			tmp = current;
			if (current->prev && current->next)
			{

			/*		If both the previous and next elements in the list		*/
			/*	exist, we can say that we are in the "middle" of the list.	*/
			/*	To remove this element, we need to use an intermediate		*/
			/*	pointer to preserve the location of the part to be removed,	*/
			/*	and then pull both ends together like a certain spider-		*/
			/*	themed superhero.											*/

				current->prev->next = current->next;
				current->next->prev = current->prev;
				current = current->next;
			}
			else if (current->next)
			{
			/*		If only the next value exists, we must be removing the	*/
			/*	first element in the linked-list. In this case, we should	*/
			/*	make sure that the "previous" value for the new "current"	*/
			/*	one is null, so we don't accidentally fool and functions 	*/
			/*	that might be made down the line.							*/

				current = current->next;
				*first = current;
				current = current->next;
				current->prev = NULL;
			}
			else if (current->prev)
			{
			/*		If we are deleting the last element in the linked-list,	*/
			/*	hurray, because that's the ideal scenario. Just remove the	*/
			/*	reference to this node and mark our current node as NULL so	*/
			/*	the loop will exit.											*/

				current->prev->next = NULL;;
				current = NULL;
			}
			else 
			{
			/*		If neither the next nor the previous values exist, this	*/
			/*	must be the last element in the linked list. Remove it, and	*/
			/*	"notify" the spawning function to create a new list.		*/
				current = NULL;
				*first = current;;
			}

			/*		Now that both ends of the list have been spliced, 		*/
			/*	unless this is the last element to be deleted, we can use	*/
			/*	our temporary pointer to free our memory, ensuring that		*/
			/*	smatrix runs smoothly and efficiently.						*/

			free(tmp->data);
			free(tmp);

		}
		else
		{
		/*		Deleting our node from the linked-list moves us forward.	*/
		/*	If no node has been deleted (or more properly, if we never		*/
		/*	tried to delete any), move on to the next node. If this node	*/
		/*	was the last one, our next node will be NULL and the loop will	*/
		/*	exit.															*/

			current = current->next;
		}
	}
	current = *first;

	for(i=0;i<terminal_dimensions->ws_row;i++){
		printf("%s", _matrix->rows[i].cells);
	}
	fflush(stdout);
}

