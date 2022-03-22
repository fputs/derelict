#include <string.h>

#include "mapping/map.h"

void generate_test(struct Map *map) {
    memset(map->tiles, TILE_WALKABLE | TILE_VISIBLE | TILE_DISCOVERED,
           sizeof(enum Tile) * map->width * map->height);

    for (int x = 0; x < map->width; x++) {
        REM_WALKABLE(tile(map, x, 0));
        REM_WALKABLE(tile(map, x, map->height - 1));
    }

    for (int y = 0; y < map->height; y++) {
        REM_WALKABLE(tile(map, 0, y));
        REM_WALKABLE(tile(map, map->width - 1, y));
    }

    map->player_start_x = 161;
    map->player_start_y = 1;
}