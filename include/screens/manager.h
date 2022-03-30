#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screens/screen.h"
#include "lfstack.h"

void init_screen_manager();

void push_screen(struct Screen *s);

void pop_screen();

struct Screen *peek_screen();

void destroy_screen_manager();

void sm_update(struct GameState *gs);

void sm_render(struct GameState *gs);

void sm_input(struct GameState *gs);

#endif
