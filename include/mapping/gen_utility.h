#ifndef MAPPING_GEN_UTILITY_H
#define MAPPING_GEN_UTILITY_H

#include "lflinkedlist.h"

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
int rand_int(int low, int high);

#endif //MAPPING_GEN_UTILITY_H
