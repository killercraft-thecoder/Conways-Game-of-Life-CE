#include <graphx.h>
#include "structure_preview.h"
#include "structures.h"

#define CELL_SIZE 4
#define GRID_W 80
#define GRID_H 60

void render_structure_preview(int structure_index, int cursor_x, int cursor_y) {
    const Structure *s = NULL;

    if (structure_index < 0 || structure_index >= structures_count()) {
        return;
    }

    s = &structures_list[structure_index]; // You will expose this in structures.c

    gfx_SetColor(200); // light gray preview color

    for (int dy = 0; dy < s->h; dy++) {
        for (int dx = 0; dx < s->w; dx++) {
            int gx = cursor_x + dx;
            int gy = cursor_y + dy;

            if (gx < 0 || gx >= GRID_W || gy < 0 || gy >= GRID_H) {
                continue;
            }

            if (s->cells[dy * s->w + dx]) {
                gfx_FillRectangle_NoClip(
                    gx * CELL_SIZE,
                    gy * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                );
            }
        }
    }
}