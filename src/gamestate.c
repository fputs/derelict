#include <stdlib.h>

#include "gamestate.h"
#include "ecs/components.h"
#include "ecs/systems.h"

// ECS Declarations
ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Movement);
ECS_COMPONENT_DECLARE(Drawable);
ECS_COMPONENT_DECLARE(Actor);

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

    ECS_SYSTEM(gs->ecs, move_system, EcsOnUpdate, Position, Movement)
    ECS_SYSTEM(gs->ecs, remove_movement_system, EcsPostUpdate, Movement);

    /* START TEMP */
    // Temp player settings
    ecs_set(gs->ecs, gs->player, Actor, {10, 5});
    ecs_set(gs->ecs, gs->player, Drawable, {'@', 0, color_from_name("yellow")});

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
