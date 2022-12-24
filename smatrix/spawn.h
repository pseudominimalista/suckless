#ifndef _spawn_h
#define _spawn_h

#include "spawn.c"

void
spawn(int spawn_tries,
      int spawn_chance,
      slist **first,
      struct winsize terminal_dimensions,
      int length_min,
      int length_max);

#endif
