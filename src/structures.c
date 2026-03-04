#include "structures.h"
#include "grid.h"

// -----------------------------
// Structure definitions
// -----------------------------

// 2x2 Block
static const uint8_t block_cells[] = {
    1,1,
    1,1
};

// Blinker (horizontal)
static const uint8_t blinker_cells[] = {
    1,1,1
};

// Glider
static const uint8_t glider_cells[] = {
    0,1,0,
    0,0,1,
    1,1,1
};

// Lightweight Spaceship (LWSS)
static const uint8_t lwss_cells[] = {
    0,1,1,1,1,
    1,0,0,0,1,
    0,0,0,0,1,
    1,0,0,1,0
};

// Gosper Glider Gun (36x9)
static const uint8_t gosper_cells[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
    0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
    1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

// MWSS (6x5)
static const uint8_t mwss_cells[] = {
    0,0,1,1,1,0,
    0,1,0,0,0,1,
    1,0,0,0,0,0,
    1,0,0,0,0,1,
    0,1,1,1,1,0,
};

// HWSS (7x5)
static const uint8_t hwss_cells[] = {
    0,0,1,1,1,1,0,
    0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,
    1,0,0,0,0,0,1,
    0,1,1,1,1,1,0,
};

// Pulsar (13x13)
static const uint8_t pulsar_cells[] = {
    0,0,1,1,1,0,0,0,1,1,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    0,0,1,1,1,0,0,0,1,1,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,0,0,0,1,1,1,0,0,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    1,0,0,0,0,1,0,1,0,0,0,0,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,0,0,0,1,1,1,0,0,
};

// Pentadecathlon (10x3)
static const uint8_t pentadecathlon_cells[] = {
    0,1,1,1,1,1,1,1,1,0,
    1,0,0,0,0,0,0,0,0,1,
    0,1,1,1,1,1,1,1,1,0,
};

// Rpent (3x3)
static const uint8_t rpent_cells[] = {
    0,1,1,
    1,1,0,
    0,1,0,
};

// Acorn (7x3)
static const uint8_t acorn_cells[] = {
    0,1,0,0,0,0,0,
    0,0,0,1,0,0,0,
    1,1,0,0,1,1,1,
};

// Diehard (8x3)
static const uint8_t diehard_cells[] = {
    0,0,0,0,0,0,1,0,
    1,1,0,0,0,0,0,0,
    0,1,0,0,0,1,1,1,
};

// -----------------------------
// Structure list
// -----------------------------

const Structure structures_list[] = {
    { "Block", 2, 2, block_cells },
    { "Blinker", 3, 1, blinker_cells },
    { "Glider", 3, 3, glider_cells },
    { "LWSS", 5, 4, lwss_cells },
    { "Gosper Gun", 36, 9, gosper_cells },
    { "MWSS", 6, 5, mwss_cells },
    { "HWSS", 7, 5, hwss_cells },
    { "Pulsar", 13, 13, pulsar_cells },
    { "Pentadecathlon", 10, 3, pentadecathlon_cells },
    { "Rpent", 3, 3, rpent_cells },
    { "Acorn", 7, 3, acorn_cells },
    { "Diehard", 8, 3, diehard_cells },
};

#define STRUCT_COUNT (sizeof(structures_list) / sizeof(Structure))

// -----------------------------
// Public API
// -----------------------------

int structures_count(void) {
    return STRUCT_COUNT;
}

const char *structures_name(int index) {
    if (index < 0 || index >= STRUCT_COUNT) return "";
    return structures_list[index].name;
}

void structures_place(unsigned int index, int x, int y) {
    if (index < 0 || index >= STRUCT_COUNT) return;

    const Structure *s = &structures_list[index];

    for (int dy = 0; dy < s->h; dy++) {
        for (int dx = 0; dx < s->w; dx++) {
            int gx = x + dx;
            int gy = y + dy;

            if (gx >= 0 && gx < 80 && gy >= 0 && gy < 60) {
                uint8_t cell = s->cells[dy * s->w + dx];
                if (cell) {
                    grid_set(gx, gy, 1);
                }
            }
        }
    }
}