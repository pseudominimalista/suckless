drop*
drop_new_random(struct winsize terminal_dimensions,
		int length_min,
		int length_max)
{
        drop *_drop = malloc(sizeof(drop));

        _drop->value = char_new_random();
        _drop->length = length_new_random(length_min, length_max);
        _drop->velocity = velocity_new_random();
        _drop->position_x = position_new_random(terminal_dimensions.ws_col);
        _drop->position_y = 0;
        return _drop;
}

