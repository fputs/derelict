#ifndef MAPPING_GEN_UTILITY_H
#define MAPPING_GEN_UTILITY_H

#include "lflinkedlist.h"
#include "mapping/map.h"

struct Room {
    int x0;
    int y0;
    int x1;
    int y1;
    int w;
    int h;
};

struct Room new_room(int x0, int y0, int w, int h);
struct Room *new_room_ptr(int x0, int y0, int w, int h);
List *new_room_list();
void del_room_list(List *list);
void room_center(struct Room *room, int* x, int *y);
int room_overlap(struct Room *r1, struct Room *r2);

void dig_horizontal_line(struct Map *map, int x0, int x1, int y);
void dig_vertical_line(struct Map *map, int y0, int y1, int x);
void dig_hallway(struct Map *map, struct Room *r1, struct Room *r2);

int rand_int(int low, int high);

#endif //MAPPING_GEN_UTILITY_H
