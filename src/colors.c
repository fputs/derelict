#include <string.h>
#include <stdio.h>

#include "colors.h"
#include "lfinput.h"

void add_color(struct DColor **colors, char *name, int a, int r, int g, int b) {
    struct DColor *c = NULL;
    HASH_FIND_STR(*colors, name, c);
    if (c == NULL) {
        c = malloc(sizeof(struct DColor));
        strcpy(c->name, name);
        HASH_ADD_STR(*colors, name, c);
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

struct DColor *load_colors(char *path) {
    struct DColor *colors = NULL;
    size_t sz = 0;
    char **lines = get_lines(path, &sz);

    for (size_t i = 0; i < sz; i++) {
        if (strcmp(lines[i], "\n") == 0) {
            continue;
        }
        int a, r, g, b;
        char name[32];
        sscanf(lines[i], "%s %d %d %d %d", name, &a, &r, &g, &b);
        add_color(&colors, name, a, r, g, b);
    }

    del_lines(lines);
    return colors;
}

void delete_colors(struct DColor *colors) {
    struct DColor *c, *t;

    HASH_ITER(hh, colors, c, t) {
        HASH_DEL(colors, c);
        free(c);
    }
}

color_t get_color(struct DColor *colors, char *name) {
    struct DColor *d;
    HASH_FIND_STR(colors, name, d);
    return d == NULL ? 0 : d->color;
}
