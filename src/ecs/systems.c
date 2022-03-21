#include "ecs/systems.h"
#include "ecs/components.h"
#include "gamestate.h"

extern ECS_DECLARE(NoQueuedMovement);

void move_system(ecs_iter_t *it) {
    struct GameState *gs = (struct GameState*)it->ctx;
    if (!gs->turn_flag) {
        return;
    }
    Position *p = ecs_term(it, Position, 1);
    Moveable *m = ecs_term(it, Moveable, 2);

    for (int i = 0; i < it->count; i++) {
        p[i].x += m[i].dx;
        p[i].y += m[i].dy;
        m[i].dx = 0;
        m[i].dy = 0;
        ecs_add_id(it->world, it->entities[i], ECS_CASE | NoQueuedMovement);
        if (it->entities[i] == gs->player) {
            gs->turn_flag = 0;
        }
    }
}

void verify_player_movement_system(ecs_iter_t *it) {
    Position *p = ecs_term(it, Position, 1);
    Moveable *m = ecs_term(it, Moveable, 2);
    struct GameState *gs = (struct GameState*)it->ctx;

    for (int i = 0; i < it->count; i++) {
        int px = p[i].x + m[i].dx;
        int py = p[i].y + m[i].dy;
        if (IS_WALKABLE(tile(gs->current_map, px, py))) {
            gs->turn_flag = 1;
        } else {
            gs->turn_flag = 0;
        }
    }
}
