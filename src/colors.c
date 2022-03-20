#include <string.h>

#include "colors.h"

void add_color(struct DColor *colors, char *name, int a, int r, int g, int b) {
    struct DColor *c = NULL;
    HASH_FIND_STR(colors, name, c);
    if (c == NULL) {
        c = malloc(sizeof(struct DColor));
        strcpy(c->name, name);
        HASH_ADD_STR(colors, name, c);
    }
    c->color = color_from_argb(a, r, g, b);
}

void clear_colors(struct DColor *colors) {
    struct DColor *c, *t;

    HASH_ITER(hh, colors, c, t) {
        HASH_DEL(colors, c);
        free(c);
    }
}

color_t* load_colors(char *path) {

}

color_t *get_color(struct DColor *colors, char *name) {

}
