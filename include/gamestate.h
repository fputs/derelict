#ifndef GAMESTATE_H
#define GAMESTATE_H

struct GameState {
    int window_width;
    int window_height;

    int quit_flag;
};

struct GameState *new_GameState(int w, int h);
void destroy_GameState(struct GameState* gs);

#endif