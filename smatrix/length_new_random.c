int
length_new_random(int length_min,
		  int length_max)
{
	int length;	

	length = (rand() % ( length_max - length_min ) ) + length_min;

	return length;
}

