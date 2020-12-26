#include "BearLibTerminal.h"

void draw_ui_box(int x, int y, int w, int h) {
    terminal_put(x, y, 0xE0DA);
    for (int bx = x + 1; bx < x + w; bx++) {
        terminal_put(bx, y, 0xE0C4);
    }
    terminal_put(x + w, y, 0xE0BF);

    terminal_put(x, y + h, 0xE0C0);
    for (int bx = x + 1; bx < x + w; bx++) {
        terminal_put(bx, y + h, 0xE0C4);
    }
    terminal_put(x + w, y + h, 0xE0D9);

    for (int by = y + 1; by < y + h; by++) {
        terminal_put(x, by, 0xE0B3);
        terminal_put(x + w, by, 0xE0B3);
    }
}