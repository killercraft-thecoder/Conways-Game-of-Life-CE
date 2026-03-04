#include <graphx.h>
#include <keypadc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "grid.h"
#include "render.h"
#include "input.h"
#include "files.h"
#include "structures.h"
#include "structure_preview.h"
#include "title.h"
#include "file_select.h"
#include "menu.h"
#include "structure_picker.h"
#include <tice.h>

#define GRID_W 80
#define GRID_H 60


typedef enum
{
    STATE_TITLE,
    STATE_FILE_SELECT,
    STATE_EDIT,
    STATE_RUN,
    STATE_MENU,
    STATE_STRUCTURE_PICKER,
    STATE_STRUCTURE_PREVIEW
} GameState;

void input_flush(void) {
    kb_Scan();
    while (kb_AnyKey()) kb_Scan();
}

int main(void)
{
    gfx_Begin();
    gfx_SetDrawBuffer();

    grid_init(GRID_W, GRID_H);

    GameState state = STATE_TITLE;
    input_flush();
    int cursor_x = 0;
    int cursor_y = 0;

    int title_index = 0;     // 0 = Play, 1 = Load, 2 = Exit
    int file_index = 0;      // index in file list
    int menu_index = 0;      // in-game menu index
    int structure_index = 0; // structure picker index

    bool ignore_input = true;

    while (true)
    {
        kb_Scan();
        input_update();

        if (kb_IsDown(kb_KeyClear))
        {
            gfx_End();
            exit(0);
        }

        switch (state)
        {

        // -------------------------------
        // TITLE SCREEN
        // -------------------------------
        case STATE_TITLE:
            if (input_cursor_dy() < 0 && title_index > 0 && !ignore_input)
                title_index--;
            if (input_cursor_dy() > 0 && title_index < 2 && !ignore_input)
                title_index++;

            
            
            if (input_enter_pressed() && !ignore_input)
            {
                if (title_index == 0)
                {
                    grid_clear();
                    state = STATE_EDIT;
                }
                else if (title_index == 1)
                {
                    files_scan();
                    file_index = 0;
                    state = STATE_FILE_SELECT;
                }
                else if (title_index == 2)
                {
                    gfx_End();
                    exit(0);
                }
            }

            if (ignore_input) {
                ignore_input = false;
            }

            render_title_screen(title_index);
            gfx_SwapDraw();
            msleep(100);
            break;

        // -------------------------------
        // FILE SELECT SCREEN
        // -------------------------------
        case STATE_FILE_SELECT:
            if (input_cursor_dy() < 0 && file_index > 0)
                file_index--;
            if (input_cursor_dy() > 0 && file_index < files_count() - 1)
                file_index++;

            if (input_enter_pressed())
            {
                files_load(file_index);
                state = STATE_EDIT;
            }

            if (kb_IsDown(kb_KeyClear))
            {
                state = STATE_TITLE;
            }

            render_file_select(file_index);
            gfx_SwapDraw();
            msleep(100);
            break;

        // -------------------------------
        // EDIT MODE
        // -------------------------------
        case STATE_EDIT:
            cursor_x += input_cursor_dx();
            cursor_y += input_cursor_dy();

            if (cursor_x < 0)
                cursor_x = 0;
            if (cursor_x >= GRID_W)
                cursor_x = GRID_W - 1;
            if (cursor_y < 0)
                cursor_y = 0;
            if (cursor_y >= GRID_H)
                cursor_y = GRID_H - 1;

            if (input_toggle_pressed())
            {
                grid_toggle(cursor_x, cursor_y);
            }

            if (input_enter_pressed())
            {
                state = STATE_RUN;
            }

            if (kb_IsDown(kb_KeyDel))
            {
                menu_index = 0;
                state = STATE_MENU;
            }

            render_grid();
            render_cursor(cursor_x, cursor_y);
            gfx_SwapDraw();
            break;

        // -------------------------------
        // RUN MODE
        // -------------------------------
        case STATE_RUN:
            grid_step();

            if (input_enter_pressed())
            {
                state = STATE_EDIT;
            }

            if (kb_IsDown(kb_KeyDel))
            {
                menu_index = 0;
                state = STATE_MENU;
            }

            render_grid();
            gfx_SwapDraw();

            msleep(10);
            break;

        // -------------------------------
        // IN-GAME MENU
        // -------------------------------
        case STATE_MENU:
            if (input_cursor_dy() < 0 && menu_index > 0)
                menu_index--;
            if (input_cursor_dy() > 0 && menu_index < 3)
                menu_index++;

            if (input_enter_pressed())
            {
                if (menu_index == 0)
                {
                    files_save();
                    state = STATE_EDIT;
                }
                else if (menu_index == 1)
                {
                    files_save();
                    state = STATE_TITLE;
                }
                else if (menu_index == 2)
                {
                    gfx_End();
                    exit(0);
                }
                else if (menu_index == 3)
                {
                    structure_index = 0;
                    state = STATE_STRUCTURE_PICKER;
                }
            }

            if (kb_IsDown(kb_KeyClear))
            {
                state = STATE_EDIT;
            }

            render_menu(menu_index);
            gfx_SwapDraw();
            break;

        // -------------------------------
        // STRUCTURE PLACEMENT
        // -------------------------------
        case STATE_STRUCTURE_PICKER:
            if (input_cursor_dy() < 0 && structure_index > 0)
                structure_index--;
            if (input_cursor_dy() > 0 && structure_index < structures_count() - 1)
                structure_index++;

            if (input_enter_pressed())
            {
                // Go to preview mode
                state = STATE_STRUCTURE_PREVIEW;
            }

            if (kb_IsDown(kb_KeyClear))
            {
                state = STATE_EDIT;
            }

            render_structure_picker(structure_index);
            gfx_SwapDraw();
            msleep(100);
            break;

        case STATE_STRUCTURE_PREVIEW:
            // Move preview cursor
            cursor_x += input_cursor_dx();
            cursor_y += input_cursor_dy();

            if (cursor_x < 0)
                cursor_x = 0;
            if (cursor_x >= GRID_W)
                cursor_x = GRID_W - 1;
            if (cursor_y < 0)
                cursor_y = 0;
            if (cursor_y >= GRID_H)
                cursor_y = GRID_H - 1;

            if (input_enter_pressed())
            {
                structures_place(structure_index, cursor_x, cursor_y);
                state = STATE_EDIT;
            }

            if (kb_IsDown(kb_KeyClear))
            {
                state = STATE_EDIT;
            }

            render_grid();
            render_structure_preview(structure_index, cursor_x, cursor_y);
            render_cursor(cursor_x, cursor_y);
            gfx_SwapDraw();
            break;
        }
    }
}