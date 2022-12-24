#include "matrix.h"

struct matrix*
matrix_new(int width, int height)
{
        int i, j;

        struct matrix *_matrix;
        row *rows = malloc(sizeof(row[height]));

	_matrix = malloc(sizeof(matrix));

        for (i=0;i<height;i++){
                char *chars = malloc(sizeof(char[width+1]));
                for (j=0;j<width;j++){
                        chars[j] = ' ';
                }
		chars[width] = '\0';
                row *_row;
                _row = malloc(sizeof(row));
                _row->cells = chars;
                _row->num_cells = width;
                _row->cells = chars;

                rows[i] = *_row;
        }

        _matrix->rows = rows;
        _matrix->num_rows = height;

        return _matrix;
}

