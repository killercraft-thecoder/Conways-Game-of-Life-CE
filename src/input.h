#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

extern bool prev_enter;

void input_update(void);
int input_cursor_dx(void);
int input_cursor_dy(void);
bool input_toggle_pressed(void);
bool input_enter_pressed(void);

#endif