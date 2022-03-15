#include <stdlib.h>

#include "screens/mainmenu.h"
#include "screens/manager.h"
#include "screens/gamescreen.h"
#include "BearLibTerminal.h"

void main_menu_input(struct GameState *gs) {
    switch (terminal_read()) {
        case TK_ESCAPE:
        case TK_CLOSE:
            gs->quit_flag = 1;
            break;

        case TK_ENTER:
            push_screen(new_gamescreen());
            break;
    }
}

void main_menu_render(struct GameState *gs) {
    terminal_clear();
    terminal_print(1, 1, "Main Menu");
    terminal_refresh();
}

void main_menu_update(struct GameState *gs) {

}

struct Screen *new_main_menu_screen() {
    struct Screen *s = malloc(sizeof(struct Screen));
    s->input = main_menu_input;
    s->render = main_menu_render;
    s->update = main_menu_update;
    return s;
}

