#include <stdlib.h>

#include "mapping/map.h"
#include "mapping/generators.h"

struct Map *init_Map(int w, int h, enum MapType type) {
    struct Map *m = malloc(sizeof(struct Map));

    m->width = w;
    m->height = h;
    m->tiles = malloc(sizeof(enum Tile) * w * h);

    switch (type) {
        case MAPTYPE_TEST:
            generate_test(m);
    }

    return m;
}

void destroy_Map(struct Map *map) {
    if (map == NULL) {
        return;
    }
    if (map->tiles != NULL) {
        free(map->tiles);
    }
    free(map);
}

inline int idx(struct Map *map, int x, int y) {
    return x + y * map->width;
}

enum Tile *tile(struct Map *map, int x, int y) {
    return &map->tiles[idx(map, x, y)];
}
