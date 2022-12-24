int
position_new_random(int terminal_width)
{
        int position_x;

	position_x = (rand() % terminal_width);

	return position_x;
}

