#include <graphx.h>
#include "render.h"
#include "grid.h"

#define CELL_SIZE 4
#define GRID_W 80
#define GRID_H 60

void render_grid(void) {
    gfx_FillScreen(0);

    gfx_SetColor(255);

    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            if (grid_get(x, y)) {
                gfx_FillRectangle_NoClip(x * CELL_SIZE,
                                         y * CELL_SIZE,
                                         CELL_SIZE,
                                         CELL_SIZE);
            }
        }
    }
}

void render_cursor(int x, int y) {
    int px = x * CELL_SIZE;
    int py = y * CELL_SIZE;

    gfx_SetColor(255);

    gfx_HorizLine(px, py, CELL_SIZE);
    gfx_HorizLine(px, py + CELL_SIZE - 1, CELL_SIZE);
    gfx_VertLine(px, py, CELL_SIZE);
    gfx_VertLine(px + CELL_SIZE - 1, py, CELL_SIZE);
}