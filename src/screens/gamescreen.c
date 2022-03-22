#include <stdlib.h>

#include "ecs/components.h"
#include "ecs/systems.h"
#include "screens/gamescreen.h"
#include "screens/manager.h"
#include "screens/utility.h"
#include "BearLibTerminal.h"
#include "layers.h"
#include "colors.h"
#include "lfmath.h"

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
    terminal_color(get_color(gs->colors, "Text"));

    // Map
    terminal_layer(LAYER_MAP);
    int map_sz_x = gs->window_width - STAT_PANEL_WIDTH - 1;
    int map_sz_y = gs->window_height - MESSAGE_LOG_HEIGHT - 1;
    const Position *pp = ecs_get(gs->ecs, gs->player, Position);
    int csx, csy;
    if (pp->x < map_sz_x / 2) {
        csx = 0;
    } else if (pp->x > gs->current_map->width - map_sz_x / 2) {
        csx = gs->current_map->width - map_sz_x + 1;
    } else {
        csx = pp->x - map_sz_x / 2;
    }
    if (pp->y < map_sz_y / 2) {
        csy = 0;
    } else if (pp->y > gs->current_map->height - map_sz_y / 2) {
        csy = gs->current_map->height - map_sz_y + 1;
    } else {
        csy = pp->y - map_sz_y / 2;
    }

    draw_ui_box(0, 0, map_sz_x, map_sz_y);
    for (int x = 1, cx = csx; x < map_sz_x; x++, cx++) {
        for (int y = 1, cy = csy; y < map_sz_y; y++, cy++) {
            enum Tile *t = tile(gs->current_map, cx, cy);
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
    static ecs_filter_t f;
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
            if (p[i].x >= csx && p[i].x <= csx + map_sz_x &&
                p[i].y >= csy && p[i].y <= csy + map_sz_y) {
                terminal_color(d[i].fg);
                terminal_printf(p[i].x - csx + 1, p[i].y - csy + 1, "%c", d[i].symbol);
            }
        }
    }

    // Stat Panel
    terminal_color(get_color(gs->colors, "Text"));
    draw_ui_box(gs->window_width - STAT_PANEL_WIDTH, 0, STAT_PANEL_WIDTH - 1, gs->window_height - 1);
    terminal_color(get_color(gs->colors, "Text"));
    terminal_print(STAT_PANEL_X_START, 1, "Stats");

    // Message Log
    terminal_color(get_color(gs->colors, "Text"));
    draw_ui_box(0, gs->window_height - MESSAGE_LOG_HEIGHT, gs->window_width - STAT_PANEL_WIDTH - 1, MESSAGE_LOG_HEIGHT - 1);
    terminal_color(get_color(gs->colors, "Text"));
    terminal_printf(1, MESSAGE_LOG_Y_START, "Player at %d,%d", pp->x, pp->y);

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

