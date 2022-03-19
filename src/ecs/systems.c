#include "ecs/systems.h"
#include "ecs/components.h"
#include "gamestate.h"

extern ECS_COMPONENT_DECLARE(Movement);

void move_system(ecs_iter_t *it) {
    struct GameState *gs = (struct GameState*)it->ctx;
    if (!gs->turn_flag) {
        return;
    }
    Position *p = ecs_term(it, Position, 1);
    Movement *m = ecs_term(it, Movement, 2);

    for (int i = 0; i < it->count; i++) {
        p[i].x += m[i].dx;
        p[i].y += m[i].dy;
    }
    gs->turn_flag = 0;
}

void remove_movement_system(ecs_iter_t *it) {
    Movement *m = ecs_term(it, Movement, 1);
    for (int i = 0; i < it->count; i++) {
        ecs_remove(it->world, it->entities[i], Movement);
    }
}

void verify_player_movement_system(ecs_iter_t *it) {
    Position *p = ecs_term(it, Position, 1);
    Movement *m = ecs_term(it, Movement, 2);
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
