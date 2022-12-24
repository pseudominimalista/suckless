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

void
spawn(int spawn_tries,
      int spawn_chance,
      slist **_first,
      struct winsize terminal_dimensions,
      int length_min,
      int length_max)
	{
     	//printf("Entering function: spawn.c\n");
        int i;

	slist *tmp, *first;
	first = *_first;

	for (i=0;i<spawn_tries;i++){
        	if (1) {     /*      Add RNG here    */
                   	drop *_drop;
                        _drop = drop_new_random(terminal_dimensions, length_min, length_max);
      	                //printf("Checking if first is null... ");
			//fflush(stdout);
			if (first == NULL){
                                //printf("Affirmative!\n");
				//printf("Creating first node in list... ");
				//fflush(stdout);
				first = slist_new(_drop);
				//printf("OK!\n");
				//printf("Data test: %c\n",first->data->value);
                        } else {
				//printf("Negative!\n");
				//first = *_first;
				//printf("Creating new slist object... ");
				//fflush(stdout);
				tmp = slist_new(_drop);
				//printf("Done!\n");
				//printf("Inserting at beginning... ");
				//fflush(stdout);
				tmp->next = first;
				//printf("Done!\n");
				first->prev = tmp;
				first = tmp;
				//printf("Address of nex beginning: %p\n",
				//	first);
				//first = tm
				//printf("Data test: %c\n",
				//	first->data->value);
			//	///printf("U");
                        }
               }
        }

	*_first = first;

	//printf("Leaving function: spawn.c\n");
        return;
}

