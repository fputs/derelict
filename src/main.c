#include <sodium.h>
#include <stdlib.h>
#include <stdio.h>

#include "BearLibTerminal.h"
#include "gamestate.h"
#include "screens/manager.h"
#include "screens/mainmenu.h"

#define INIT_TERM_WIDTH 100
#define INIT_TERM_HEIGHT 60
#define INIT_FONT_SZ 12

int main() {
    // INIT GAME
    if (sodium_init() == -1) {
        printf("Failed to init libsodium");
        exit(EXIT_FAILURE);
    }
    terminal_open();
    terminal_setf("window: title='foo', size=%dx%d;", INIT_TERM_WIDTH, INIT_TERM_HEIGHT);
    terminal_setf("font: resources/ProggySquare.ttf, size=%dx%d;", INIT_FONT_SZ, INIT_FONT_SZ);
    terminal_set("0xE000: resources/Cheepicus_12x12.png, size=12x12");

    struct GameState *gs = new_GameState(INIT_TERM_WIDTH, INIT_TERM_HEIGHT, "resources/colors");
    init_screen_manager();
    push_screen(new_main_menu_screen());

    // RUN GAME
    while (!gs->quit_flag) {
        sm_render(gs);
        sm_input(gs);
        sm_update(gs);
    }

    // END GAME
    destroy_screen_manager();
    destroy_GameState(gs);
    terminal_close();
    return 0;
}
