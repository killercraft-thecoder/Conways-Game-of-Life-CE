#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdint.h>

typedef struct {
    const char *name;
    uint8_t w, h;
    const uint8_t *cells;   // row-major 0/1 pattern
} Structure;

int structures_count(void);
const char *structures_name(int index);
void structures_place(unsigned int index, int x, int y);

extern const Structure structures_list[];

#endif