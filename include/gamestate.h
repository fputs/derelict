#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "flecs.h"
#include "mapping/map.h"

struct GameState {
    int window_width;
    int window_height;

    struct Map *current_map;
    ecs_world_t *ecs;

    int quit_flag;
};

struct GameState *new_GameState(int w, int h);
void destroy_GameState(struct GameState* gs);

#endif