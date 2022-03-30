#ifndef SCREENS_SCREEN_H
#define SCREENS_SCREEN_H

#include "gamestate.h"

typedef void (*screen_func)(struct GameState *gs);

struct Screen {
    screen_func update;
    screen_func render;
    screen_func input;
};

#endif
