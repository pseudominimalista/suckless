
void
frame_buffer_update( struct winsize *terminal_dimensions)
{
        int i, j;

        i = 0;
        j = 0;

        /*      Create array and initialize with spaces.
         *      ToDo: Reuse array if terminal size is unchanged
         */


        //frame_buffer =
        frame_buffer = malloc(sizeof(
                gchar[terminal_dimensions->ws_col * terminal_dimensions->ws_row +terminal_dimensions->ws_row]) );

        //printf("Terminal: %ldx%ld\n", TERMINAL_WIDTH, TERMINAL_HEIGHT);

        for (i=0;i<terminal_dimensions->ws_row;i++){
                for (j=0;j<terminal_dimensions->ws_col - 1;j++){
                        frame_buffer[i * ( terminal_dimensions->ws_col ) + j] = 'A';
                }
                frame_buffer[i * ( terminal_dimensions->ws_col + 1)
                             + terminal_dimensions->ws_col] = 'R';

        }
        return;
}

