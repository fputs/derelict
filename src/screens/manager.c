#include <stdlib.h>

#include "screens/manager.h"

struct Stack *screen_manager;

void init_screen_manager() {
    screen_manager = malloc(sizeof(struct Stack));
    stack_init(screen_manager, free);
}

void push_screen(struct Screen *s) {
    stack_push(screen_manager, s);
}

void pop_screen() {
    void *data;
    stack_pop(screen_manager, &data);
}

struct Screen *peek_screen() {
    return (struct Screen*)stack_peek(screen_manager);
}

void destroy_screen_manager() {
    stack_destroy(screen_manager);
    screen_manager = NULL;
}

void sm_update(struct GameState *gs) {
    peek_screen()->update(gs);
}

void sm_render(struct GameState *gs) {
    peek_screen()->render(gs);
}

void sm_input(struct GameState *gs) {
    peek_screen()->input(gs);
}

