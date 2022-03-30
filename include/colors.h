#ifndef COLORS_H
#define COLORS_H

#include "BearLibTerminal.h"
#include "uthash.h"

struct DColor {
    char name[16];
    color_t color;
    UT_hash_handle hh;
};

struct DColor *load_colors(char *);

void clear_colors(struct DColor *);

color_t get_color(struct DColor *, char *);

#endif // COLORS_H
