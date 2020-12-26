#ifndef MAPPING_MAP_H
#define MAPPING_MAP_H

enum Tile {
    TILE_NONE       = 0,
    TILE_WALKABLE   = 1 << 0,
    TILE_VISIBLE    = 1 << 1,
    TILE_DISCOVERED = 1 << 2,
};

enum MapType {
    MAPTYPE_TEST,
};

struct Map {
    int width;
    int height;
    enum Tile *tiles;
};

struct Map *init_Map(int w, int h, enum MapType type);
void destroy_Map(struct Map *map);
int idx(struct Map *map, int x, int y);
enum Tile *tile(struct Map *map, int x, int y);

#define IS_WALKABLE(t) ((TILE_WALKABLE) & (*t))
#define IS_VISIBLE(t) ((TILE_VISIBLE) & (*t))
#define IS_DISCOVERED(t) ((TILE_DISCOVERED) & (*t))
#define SET_WALKABLE(t) ((*t) |= (TILE_WALKABLE))
#define SET_VISIBLE(t) ((*t) |= (TILE_VISIBLE))
#define SET_DISCOVERED(t) ((*t) |= (TILE_DISCOVERED))
#define REM_WALKABLE(t) ((*t) &= ~(TILE_WALKABLE))
#define REM_VISIBLE(t) ((*t) &= ~(TILE_VISIBLE))
#define REM_DISCOVERED(t) ((*t) &= ~(TILE_DISCOVERED))

#endif