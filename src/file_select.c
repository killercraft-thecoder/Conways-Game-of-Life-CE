#include <graphx.h>
#include <string.h>
#include "file_select.h"
#include "files.h"

#define SCREEN_W 320
#define SCREEN_H 240

// Center text helper
static void draw_centered_text(const char *text, int y) {
    int w = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, (SCREEN_W - w) / 2, y);
}

void render_file_select(int selected) {
    gfx_FillScreen(0);
    gfx_SetTextFGColor(254);
    gfx_SetColor(255);

    // Title
    draw_centered_text("Select Save File:", 20);

    int count = files_count();
    int start_y = 60;
    int line_spacing = 18;

    for (int i = 0; i < count; i++) {
        int y = start_y + i * line_spacing;

        // Draw arrow for selected item
        if (i == selected) {
            gfx_PrintStringXY(">", (SCREEN_W / 2) - 60, y);
        }

        // Draw filename centered
        draw_centered_text(files_name(i), y);
    }

    // If no files exist
    if (count == 0) {
        draw_centered_text("(No save files found)", 120);
    }
}