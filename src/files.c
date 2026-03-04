#include <fileioc.h>
#include <string.h>
#include <stdlib.h>
#include "files.h"
#include "grid.h"

#define MAX_FILES 100
#define NAME_LEN  9   // 8 chars + null terminator

static char filenames[MAX_FILES][NAME_LEN];
static int file_count = 0;

int files_count(void) {
    return file_count;
}

const char *files_name(int index) {
    if (index < 0 || index >= file_count) return "";
    return filenames[index];
}

static int extract_index(const char *name) {
    return (name[4] - '0') * 10 + (name[5] - '0');
}

static int compare_names(const void *a, const void *b) {
    const char *A = *(const char **)a;
    const char *B = *(const char **)b;
    return extract_index(A) - extract_index(B);
}

void files_scan(void) {
    file_count = 0;
    void *search_pos = NULL;
    uint8_t type;

    while (1) {
        const char *name = ti_DetectAny(&search_pos, "", &type);
        if (!name) break;

        if (type == OS_TYPE_APPVAR && strncmp(name, "CGLS", 4) == 0) {
            strncpy(filenames[file_count], name, NAME_LEN - 1);
            filenames[file_count][NAME_LEN - 1] = '\0';
            file_count++;
        }
    }

    // Sort by index (CGLS00, CGLS01, ...)
    if (file_count > 1) {
        qsort(filenames, file_count, NAME_LEN, (int (*)(const void *, const void *))strcmp);
    }
}

void files_load(int index) {
    if (index < 0 || index >= file_count) return;

    ti_var_t slot = ti_Open(filenames[index], "r");
    if (!slot) return;

    uint16_t count;
    ti_Read(&count, sizeof(uint16_t), 1, slot);

    grid_clear();

    for (uint16_t i = 0; i < count; i++) {
        uint8_t xy[2];
        ti_Read(xy, 2, 1, slot);
        grid_set(xy[0], xy[1], 1);
    }

    ti_Close(slot);
}

void files_save(void) {
    char name[9];
    for (int i = 0; i < 100; i++) {
        sprintf(name, "CGLS%02d", i);
        if (!ti_Open(name, "r")) break;
    }

    ti_var_t slot = ti_Open(name, "w");
    if (!slot) return;

    uint16_t count = 0;
    for (int y = 0; y < 60; y++) {
        for (int x = 0; x < 80; x++) {
            if (grid_get(x, y)) count++;
        }
    }

    ti_Write(&count, sizeof(uint16_t), 1, slot);

    for (int y = 0; y < 60; y++) {
        for (int x = 0; x < 80; x++) {
            if (grid_get(x, y)) {
                uint8_t xy[2] = {x, y};
                ti_Write(xy, 2, 1, slot);
            }
        }
    }

    ti_Close(slot);
}