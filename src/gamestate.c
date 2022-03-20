#include <stdlib.h>

#include "gamestate.h"
#include "ecs/components.h"
#include "ecs/systems.h"

// ECS Declarations
ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Movement);
ECS_COMPONENT_DECLARE(Drawable);
ECS_COMPONENT_DECLARE(Actor);
ECS_COMPONENT_DECLARE(Hero);
ECS_DECLARE(QueuedMovement);
ECS_DECLARE(NoQueuedMovement);

struct GameState *new_GameState(int w, int h) {
    struct GameState *gs = malloc(sizeof(struct GameState));

    gs->window_width = w;
    gs->window_height = h;

    gs->ecs = ecs_init();

    // Setup pipeline
    ECS_TAG(gs->ecs, PreUpdate)
    ECS_TAG(gs->ecs, Update)
    ECS_TAG(gs->ecs, PostUpdate)
    ECS_TAG(gs->ecs, Render)
    ECS_TAG(gs->ecs, PostRender)
    ECS_PIPELINE(gs->ecs, DerelictPipeline, PreUpdate, Update, PostUpdate, Render, PostRender);
    ecs_set_pipeline(gs->ecs, DerelictPipeline);

    // Component definitions
    ECS_COMPONENT_DEFINE(gs->ecs, Position)
    ECS_COMPONENT_DEFINE(gs->ecs, Drawable)
    ECS_COMPONENT_DEFINE(gs->ecs, Actor)
    ECS_COMPONENT_DEFINE(gs->ecs, Movement)
    ECS_COMPONENT_DEFINE(gs->ecs, Hero)

    // Tag definitions
    ECS_TAG_DEFINE(gs->ecs, QueuedMovement)
    ECS_TAG_DEFINE(gs->ecs, NoQueuedMovement)
    ECS_TYPE(gs->ecs, MovementState, QueuedMovement, NoQueuedMovement)

    // System definitions
    ecs_system_init(gs->ecs, &(ecs_system_desc_t) {
            .query.filter.terms = {
                    {ecs_id(Position)},
                    {ecs_id(Movement)},
            },
            .entity.add = PreUpdate,
            .callback = verify_player_movement_system,
            .ctx = gs,
    });
    //ECS_SYSTEM(gs->ecs, monster_ai_system, PreUpdate, Position, Movement)
    ecs_system_init(gs->ecs, &(ecs_system_desc_t) {
            .query.filter.terms = {
                    {ecs_id(Position)},
                    {ecs_id(Movement)},
            },
            .entity.add = Update,
            .callback = move_system,
            .ctx = gs,
    });

    /* START TEMP */
    // Temp player settings
    gs->player = ecs_new_id(gs->ecs);
    ecs_set(gs->ecs, gs->player, Actor, {10, 5});
    ecs_set(gs->ecs, gs->player, Drawable, {'@', 0, color_from_name("yellow")});
    ecs_set(gs->ecs, gs->player, Hero, {1});
    ecs_add_id(gs->ecs, gs->player, ECS_SWITCH | MovementState);
    ecs_add_id(gs->ecs, gs->player, ECS_CASE | NoQueuedMovement);

    // Temp map
    gs->current_map = init_Map(w * 2, h * 2, MAPTYPE_TEST);
    ecs_set(gs->ecs, gs->player, Position, {gs->current_map->player_start_x, gs->current_map->player_start_y});
    /* END TEMP */

    // Flags
    gs->quit_flag = 0;
    gs->turn_flag = 0;

    return gs;
}

void destroy_GameState(struct GameState* gs) {
    destroy_Map(gs->current_map);
    free(gs);
}
