#include <stdint.h>
#include "grid.h"

static int grid_w;
static int grid_h;

static uint8_t *grid_data = NULL;
static uint8_t *next_data = NULL;

#define CELL(x, y) grid_data[(y) * grid_w + (x)]
#define NEXT(x, y) next_data[(y) * grid_w + (x)]

void grid_init(int w, int h) {
    grid_w = w;
    grid_h = h;

    grid_data = malloc(w * h);
    next_data = malloc(w * h);

    for (int i = 0; i < w * h; i++) {
        grid_data[i] = 0;
        next_data[i] = 0;
    }
}

void grid_toggle(int x, int y) {
    CELL(x, y) ^= 1;
}

void grid_set(int x, int y, uint8_t value) {
    CELL(x, y) = value ? 1 : 0;
}

uint8_t grid_get(int x, int y) {
    return CELL(x, y);
}

void grid_clear(void) {
    for (int i = 0; i < grid_w * grid_h; i++) {
        grid_data[i] = 0;
    }
}

static int count_neighbors(int x, int y) {
    int n = 0;

    if (y > 0 && x > 0) n += CELL(x-1, y-1);
    if (y > 0) n += CELL(x, y-1);
    if (y > 0 && x < grid_w-1) n += CELL(x+1, y-1);

    if (x > 0) n += CELL(x-1, y);
    if (x < grid_w-1) n += CELL(x+1, y);

    if (y < grid_h-1 && x > 0) n += CELL(x-1, y+1);
    if (y < grid_h-1) n += CELL(x, y+1);
    if (y < grid_h-1 && x < grid_w-1) n += CELL(x+1, y+1);

    return n;
}

void grid_step(void) {
    for (int y = 0; y < grid_h; y++) {
        for (int x = 0; x < grid_w; x++) {
            int n = count_neighbors(x, y);
            uint8_t alive = CELL(x, y);

            if (alive) {
                NEXT(x, y) = (n == 2 || n == 3);
            } else {
                NEXT(x, y) = (n == 3);
            }
        }
    }

    for (int i = 0; i < grid_w * grid_h; i++) {
        grid_data[i] = next_data[i];
    }
}