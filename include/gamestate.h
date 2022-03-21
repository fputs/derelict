#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "flecs.h"
#include "mapping/map.h"
#include "colors.h"

struct GameState {
    int window_width;
    int window_height;

    struct Map *current_map;
    struct DColor *colors;

    ecs_world_t *ecs;
    ecs_entity_t player;

    int quit_flag;
    int turn_flag;
};

struct GameState *new_GameState(int w, int h, char *color_path);
void destroy_GameState(struct GameState* gs);

#endif