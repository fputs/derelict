#include <stdlib.h>

#include "ecs/components.h"
#include "ecs/systems.h"
#include "screens/gamescreen.h"
#include "screens/manager.h"
#include "screens/utility.h"
#include "BearLibTerminal.h"
#include "layers.h"
#include "colors.h"

#define STAT_PANEL_WIDTH 20
#define STAT_PANEL_X_START gs->window_width - (STAT_PANEL_WIDTH) + 1

#define MESSAGE_LOG_HEIGHT 20
#define MESSAGE_LOG_Y_START gs->window_height - (MESSAGE_LOG_HEIGHT) + 1

extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Moveable);
extern ECS_COMPONENT_DECLARE(Drawable);
extern ECS_COMPONENT_DECLARE(Actor);
extern ECS_DECLARE(QueuedMovement);

void gamescreen_handle_input(struct GameState *gs) {
    switch (terminal_read()) {
        case TK_CLOSE:
            gs->quit_flag = 1;
            break;

        case TK_ESCAPE:
            pop_screen();
            break;

    case TK_H:
    case TK_LEFT:
        ecs_set(gs->ecs, gs->player, Moveable, {-1, 0});
        ecs_add_id(gs->ecs, gs->player, ECS_CASE | QueuedMovement);
        break;

    case TK_L:
    case TK_RIGHT:
        ecs_set(gs->ecs, gs->player, Moveable, {1, 0});
        ecs_add_id(gs->ecs, gs->player, ECS_CASE | QueuedMovement);
        break;

    case TK_K:
    case TK_UP:
        ecs_set(gs->ecs, gs->player, Moveable, {0, -1});
        ecs_add_id(gs->ecs, gs->player, ECS_CASE | QueuedMovement);
        break;

    case TK_J:
    case TK_DOWN:
        ecs_set(gs->ecs, gs->player, Moveable, {0, 1});
        ecs_add_id(gs->ecs, gs->player, ECS_CASE | QueuedMovement);
        break;
    }
}

void gamescreen_render(struct GameState *gs) {
    terminal_clear();

    // Map
    terminal_layer(LAYER_MAP);
    int map_sz_x = gs->window_width - STAT_PANEL_WIDTH - 1;
    int map_sz_y = gs->window_height - MESSAGE_LOG_HEIGHT - 1;
    draw_ui_box(0, 0, map_sz_x, map_sz_y);
    for (int x = 1; x < map_sz_x - 1; x++) {
        for (int y = 1; y < map_sz_y - 1; y++) {
            enum Tile *t = tile(gs->current_map, x - 1, y - 1);
            if (IS_WALKABLE(t)) {
                terminal_bkcolor(get_color(gs->colors, "FloorBackgroundFov"));
                terminal_color(get_color(gs->colors, "FloorFov"));
                terminal_print(x, y, ".");
            } else {
                terminal_bkcolor(get_color(gs->colors, "WallBackgroundFov"));
                terminal_color(get_color(gs->colors, "WallFov"));
                terminal_print(x, y, "#");
            }
        }
    }

    // Actors
    terminal_layer(LAYER_ACTOR);
    ecs_filter_t f;
    ecs_filter_init(gs->ecs, &f, &(ecs_filter_desc_t) {
            .terms = {
                    { ecs_id(Position) },
                    { ecs_id(Actor) },
                    { ecs_id(Drawable) },
            }
    });
    ecs_iter_t it = ecs_filter_iter(gs->ecs, &f);
    while (ecs_filter_next(&it)) {
        Position *p = ecs_term(&it, Position, 1);
        Drawable *d = ecs_term(&it, Drawable, 3);
        for (int i = 0; i < it.count; i ++) {
            // TODO: Fix this +1 garbage
            terminal_color(get_color(gs->colors, "Player"));
            terminal_printf(p[i].x + 1, p[i].y + 1, "%c", d[i].symbol);
        }
    }

    // Stat Panel
    draw_ui_box(gs->window_width - STAT_PANEL_WIDTH, 0, STAT_PANEL_WIDTH - 1, gs->window_height - 1);
    terminal_print(STAT_PANEL_X_START, 1, "Stats");

    // Message Log
    draw_ui_box(0, gs->window_height - MESSAGE_LOG_HEIGHT, gs->window_width - STAT_PANEL_WIDTH - 1, MESSAGE_LOG_HEIGHT - 1);
    terminal_print(1, MESSAGE_LOG_Y_START, "Message Log");

    terminal_refresh();
}

void gamescreen_update(struct GameState *gs) {
    ecs_progress(gs->ecs, 0);
}

struct Screen *new_gamescreen() {
    struct Screen *s = malloc(sizeof(struct Screen));
    s->input = gamescreen_handle_input;
    s->render = gamescreen_render;
    s->update = gamescreen_update;
    return s;
}

