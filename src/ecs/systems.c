#include "ecs/systems.h"
#include "ecs/components.h"

extern ECS_COMPONENT_DECLARE(Movement);

void move_system(ecs_iter_t *it) {
    Position *p = ecs_term(it, Position, 1);
    Movement *m = ecs_term(it, Movement, 2);

    for (int i = 0; i < it->count; i++) {
        p[i].x += m[i].dx;
        p[i].y += m[i].dy;
    }
}

void remove_movement_system(ecs_iter_t *it) {
    Movement *m = ecs_term(it, Movement, 1);
    for (int i = 0; i < it->count; i++) {
        ecs_remove(it->world, it->entities[i], Movement);
    }
}
