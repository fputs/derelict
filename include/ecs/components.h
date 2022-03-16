#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include "BearLibTerminal.h"

typedef struct {
    int x, y;
} Position;

typedef struct {
    char symbol;
    color_t bg;
    color_t fg;
} Drawable;

typedef struct {
    int actions;
    int hp;
    int speed;
} Character;

#endif // ECS_COMPONENTS_H
