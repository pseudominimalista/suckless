#ifndef _drop_new_random_h
#define _drop_new_random_h

#include "length_new_random.h"
#include "position_new_random.h"
#include "velocity_new_random.h"

#include "drop_new_random.c"

drop*
drop_new_random(struct winsize terminal_dimensions,
		int length_min,
		int length_max);

#endif
