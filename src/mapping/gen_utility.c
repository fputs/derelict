#include <stdlib.h>
#include <sodium.h>

#include "mapping/gen_utility.h"

struct Room new_room(int x0, int y0, int w, int h) {
    struct Room r = {x0, y0, x0 + w, y0 + h, w, h};
    return r;
}

struct Room *new_room_ptr(int x0, int y0, int w, int h) {
    struct Room *r = malloc(sizeof(struct Room));
    r->x0 = x0;
    r->y0 = y0;
    r->x1 = x0 + w;
    r->y1 = y0 + h;
    r->w = w;
    r->h = h;
    return r;
}

List *new_room_list() {
    List *list = malloc(sizeof(List));
    ll_init(list, free);
    return list;
}

void del_room_list(List* list) {
    ll_destroy(list);
    free(list);
}

void room_center(struct Room *room, int* x, int *y) {
    *x = (room->x0 + room->x1) / 2;
    *y = (room->y0 + room->y1) / 2;
}

int room_overlap(struct Room *r1, struct Room *r2) {
    if (r1->x0 <= r2->x1 && r1->x1 >= r2->x0 && r1->y0 <= r2->y1 && r1->y1 >= r2->y0) {
        return 1;
    }
    return 0;
}

int rand_int(int low, int high) {
    return (int) randombytes_uniform(high - low + 1) + low;
}
