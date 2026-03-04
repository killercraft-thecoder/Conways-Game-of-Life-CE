#ifndef GRID_FH
#define GRID_FH

#include <stdint.h>
#include <stdlib.h>

void grid_init(int w, int h);
void grid_toggle(int x, int y);
void grid_set(int x, int y, uint8_t value);
void grid_clear(void);
void grid_step(void);
uint8_t grid_get(int x, int y);

#endif