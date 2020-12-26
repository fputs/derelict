#include <stdlib.h>

#include "screens/dungeon.h"
#include "screens/manager.h"
#include "screens/utility.h"
#include "BearLibTerminal.h"

#define STAT_PANEL_WIDTH 20
#define STAT_PANEL_X_START gs->window_width - (STAT_PANEL_WIDTH) + 1

#define MESSAGE_LOG_HEIGHT 20
#define MESSAGE_LOG_Y_START gs->window_height - (MESSAGE_LOG_HEIGHT) + 1

void dungeon_input(struct GameState *gs) {
    switch (terminal_read()) {
        case TK_CLOSE:
            gs->quit_flag = 1;
            break;

        case TK_ESCAPE:
            pop_screen();
            break;
    }
}

void dungeon_render(struct GameState *gs) {
    terminal_clear();

    // Map
    draw_ui_box(0, 0, gs->window_width - STAT_PANEL_WIDTH - 1, gs->window_height - MESSAGE_LOG_HEIGHT - 1);
    terminal_print(1, 1, "Map");

    // Stat Panel
    draw_ui_box(gs->window_width - STAT_PANEL_WIDTH, 0, STAT_PANEL_WIDTH - 1, gs->window_height - 1);
    terminal_print(STAT_PANEL_X_START, 1, "Stats");

    // Message Log
    draw_ui_box(0, gs->window_height - MESSAGE_LOG_HEIGHT, gs->window_width - STAT_PANEL_WIDTH - 1, MESSAGE_LOG_HEIGHT - 1);
    terminal_print(1, MESSAGE_LOG_Y_START, "Message Log");

    terminal_refresh();
}

void dungeon_update(struct GameState *gs) {

}

struct Screen *new_dungeon_screen() {
    struct Screen *s = malloc(sizeof(struct Screen));
    s->input = dungeon_input;
    s->render = dungeon_render;
    s->update = dungeon_update;
    return s;
}

