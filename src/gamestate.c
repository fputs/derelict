#include <stdlib.h>

#include "gamestate.h"
#include "ecs/components.h"

// ECS Declarations
extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Movement);
extern ECS_COMPONENT_DECLARE(Drawable);
extern ECS_COMPONENT_DECLARE(Actor);

struct GameState *new_GameState(int w, int h) {
    struct GameState *gs = malloc(sizeof(struct GameState));

    gs->window_width = w;
    gs->window_height = h;

    gs->ecs = ecs_init();
    gs->player = ecs_new_id(gs->ecs);

    ECS_COMPONENT_DEFINE(gs->ecs, Position);
    ECS_COMPONENT_DEFINE(gs->ecs, Drawable);
    ECS_COMPONENT_DEFINE(gs->ecs, Actor);
    ECS_COMPONENT_DEFINE(gs->ecs, Movement);

    /* START TEMP */
    // Temp player settings
    ecs_set(gs->ecs, gs->player, Actor, {10, 5});
    ecs_set(gs->ecs, gs->player, Drawable, {'@', color_from_name("black"), color_from_name("white")});

    // Temp map
    gs->current_map = init_Map(w * 2, h * 2, MAPTYPE_TEST);
    ecs_set(gs->ecs, gs->player, Position, {gs->current_map->player_start_x, gs->current_map->player_start_y});
    /* END TEMP */

    gs->quit_flag = 0;

    return gs;
}

void destroy_GameState(struct GameState* gs) {
    destroy_Map(gs->current_map);
    free(gs);
}
