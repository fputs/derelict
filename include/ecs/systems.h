#ifndef ECS_SYSTEMS_H
#define ECS_SYSTEMS_H

#include "flecs.h"

void move_system(ecs_iter_t *);
void remove_movement_system(ecs_iter_t *);

#endif // ECS_SYSTEMS_H