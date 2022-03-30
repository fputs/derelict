#include <stdlib.h>
#include <string.h>

#include "mapping/map.h"
#include "mapping/gen_utility.h"

#define MAX_ROOMS 200
#define MIN_ROOM_SZ 8
#define MAX_ROOM_SZ 26

void generate_test(struct Map *map) {
    memset(map->tiles, TILE_VISIBLE | TILE_DISCOVERED,
           sizeof(enum Tile) * map->width * map->height);
    List *rooms = new_room_list();

    for (int i = 0; i < MAX_ROOMS; i++) {
        int rw = rand_int(MIN_ROOM_SZ, MAX_ROOM_SZ);
        int rh = rand_int(MIN_ROOM_SZ, MAX_ROOM_SZ);
        int rx = rand_int(0, map->width - rw - 1);
        int ry = rand_int(0, map->height - rh - 1);

        struct Room *r = new_room_ptr(rx, ry, rw, rh);

        if (rooms->size == 0) {
            ll_ins_next(rooms, rooms->tail, r);
            room_center(r, &(map->player_start_x), &(map->player_start_y));
        } else {
            int valid = 1;
            LL_ITER(rooms) {
                struct Room *t = (struct Room *) node->data;
                if (room_overlap(r, t)) {
                    valid = 0;
                    break;
                }
            }

            if (valid) {
                ll_ins_next(rooms, rooms->tail, r);
            } else {
                free(r);
            }
        }
    }

    LL_ITER(rooms) {
        struct Room *r = (struct Room *) node->data;
        for (int x = r->x0 + 1; x < r->x1; x++) {
            for (int y = r->y0 + 1; y < r->y1; y++) {
                SET_WALKABLE(tile(map, x, y));
            }
        }
        if (node->next != NULL) {
            dig_hallway(map, node->data, node->next->data);
        }
    }
    del_room_list(rooms);
}