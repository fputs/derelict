#include <stdlib.h>

#include "gamestate.h"

struct GameState *new_GameState(int w, int h) {
    struct GameState *gs = malloc(sizeof(struct GameState));

    gs->window_width = w;
    gs->window_height = h;

    // Temp map
    gs->current_map = init_Map(w * 2, h * 2, MAPTYPE_TEST);

    gs->quit_flag = 0;

    return gs;
}

void destroy_GameState(struct GameState* gs) {
    destroy_Map(gs->current_map);
    free(gs);
}
