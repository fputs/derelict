#include <stdlib.h>

#include "gamestate.h"

struct GameState *new_GameState(int w, int h) {
    struct GameState *gs = malloc(sizeof(struct GameState));

    gs->window_width = w;
    gs->window_height = h;

    gs->quit_flag = 0;

    return gs;
}

void destroy_GameState(struct GameState* gs) {
    free(gs);
}
