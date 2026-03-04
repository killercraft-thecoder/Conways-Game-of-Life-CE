#include <graphx.h>
#include <string.h>
#include "title.h"

#define SCREEN_W 320
#define SCREEN_H 240

// Menu items
static const char *menu_items[] = {
    "Play New Game",
    "Load Game",
    "Exit"
};

#define MENU_COUNT 3

// Center text helper
static void draw_centered_text(const char *text, int y) {
    int w = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, (SCREEN_W - w) / 2, y);
}

void render_title_screen(int selected) {
    gfx_FillScreen(0);
    gfx_SetTextFGColor(254);
    gfx_SetColor(255);

    // Title
    const char *title = "Conway's Game of Life CE";
    int title_y = 40;
    draw_centered_text(title, title_y);

    // Menu start position
    int start_y = title_y + 40;
    int line_spacing = 20;

    for (int i = 0; i < MENU_COUNT; i++) {
        int y = start_y + i * line_spacing;

        // Draw arrow for selected item
        if (i == selected) {
            gfx_PrintStringXY(">", (SCREEN_W / 2) - 60, y);
        }

        draw_centered_text(menu_items[i], y);
    }
}