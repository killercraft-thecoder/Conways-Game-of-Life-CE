#include <graphx.h>
#include <string.h>
#include "structure_picker.h"
#include "structures.h"


#define SCREEN_W 320
#define SCREEN_H 240

// Helper: draw centered text
static void draw_centered_text(const char *text, int y) {
    int w = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, (SCREEN_W - w) / 2, y);
}

void render_structure_picker(int selected) {
    gfx_FillScreen(0);
    gfx_SetTextFGColor(254);
    gfx_SetColor(255);

    // Title
    draw_centered_text("Place Structure:", 20);

    int count = structures_count();
    int start_y = 60;
    int line_spacing = 18;

    for (int i = 0; i < count; i++) {
        int y = start_y + i * line_spacing;

        // Arrow indicator
        if (i == selected) {
            gfx_PrintStringXY(">", (SCREEN_W / 2) - 60, y);
        }

        // Structure name
        draw_centered_text(structures_name(i), y);
    }

    // If no structures exist (unlikely)
    if (count == 0) {
        draw_centered_text("(No structures available)", 120);
    }
}