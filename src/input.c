#include <keypadc.h>
#include <stdbool.h>
#include "input.h"

static bool prev_2nd = false;
bool prev_enter = false;

void input_update(void) {
    kb_Scan();
}

int input_cursor_dx(void) {
    if (kb_IsDown(kb_KeyLeft)) return -1;
    if (kb_IsDown(kb_KeyRight)) return 1;
    return 0;
}

int input_cursor_dy(void) {
    if (kb_IsDown(kb_KeyUp)) return -1;
    if (kb_IsDown(kb_KeyDown)) return 1;
    return 0;
}

bool input_toggle_pressed(void) {
    bool now = kb_IsDown(kb_Key2nd);
    bool pressed = (now && !prev_2nd);
    prev_2nd = now;
    return pressed;
}

bool input_enter_pressed(void) {
    bool now = kb_IsDown(kb_KeyEnter);
    bool pressed = (now && !prev_enter);
    prev_enter = now;
    return pressed;
}