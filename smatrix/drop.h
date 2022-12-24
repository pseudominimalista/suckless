typedef struct
drop {
        char value;    /*      Value of character at the moment        */
        int length;   /*      Length of rain streak, is number of chars to tail (0-...)       */
        int velocity; /*      Velocity is chance over 10  to move per cycle (1-10)    */

        int position_x;       /*      Current position of the cell on x axis  */
        int position_y;       /*      Current position of the cell on y axis  */
} drop;

