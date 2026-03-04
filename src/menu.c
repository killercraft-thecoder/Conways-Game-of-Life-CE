#include <graphx.h>
#include <string.h>
#include "menu.h"

#define SCREEN_W 320
#define SCREEN_H 240

// Menu items
static const char *menu_items[] = {
    "Save",
    "Save & Quit",
    "Exit",
    "Place Structure"
};

#define MENU_COUNT 4

// Helper: centered text
static void draw_centered_text(const char *text, int y) {
    int w = gfx_GetStringWidth(text);
    gfx_PrintStringXY(text, (SCREEN_W - w) / 2, y);
}

void render_menu(int selected) {
    gfx_FillScreen(0);
    gfx_SetTextFGColor(254);
    gfx_SetColor(255);

    // Title
    draw_centered_text("Menu", 20);

    int start_y = 60;
    int line_spacing = 18;

    for (int i = 0; i < MENU_COUNT; i++) {
        int y = start_y + i * line_spacing;

        // Arrow indicator
        if (i == selected) {
            gfx_PrintStringXY(">", (SCREEN_W / 2) - 60, y);
        }

        draw_centered_text(menu_items[i], y);
    }
}