#include <stdlib.h>

#include "gamestate.h"
#include "ecs/components.h"

struct GameState *new_GameState(int w, int h) {
    struct GameState *gs = malloc(sizeof(struct GameState));

    gs->window_width = w;
    gs->window_height = h;

    gs->ecs = ecs_init();
    ECS_COMPONENT(gs->ecs, Position);
    ECS_COMPONENT(gs->ecs, Drawable);
    ECS_COMPONENT(gs->ecs, Character);

    // Temp map
    gs->current_map = init_Map(w * 2, h * 2, MAPTYPE_TEST);

    gs->quit_flag = 0;

    return gs;
}

void destroy_GameState(struct GameState* gs) {
    destroy_Map(gs->current_map);
    free(gs);
}
