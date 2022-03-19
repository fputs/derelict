#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include "BearLibTerminal.h"
#include "flecs.h"

typedef struct {
    int x, y;
} Position;

typedef struct {
    int dx, dy;
} Movement;

typedef struct {
    char symbol;
    color_t bg;
    color_t fg;
} Drawable;

typedef struct {
    int hp;
    int speed;
} Actor;

#endif // ECS_COMPONENTS_H