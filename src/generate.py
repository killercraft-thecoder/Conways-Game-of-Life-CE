# generate.py
#
# Define any number of Life structures using sparse coordinate lists.
# This script outputs C code for each structure:
#   - static const uint8_t <name>_cells[] = { ... };
#   - width, height
#
# You paste the output directly into structures.c

structures = {

    "MWSS": {
        "size": (6, 5),
        "cells": [
            (2,0),(3,0),(4,0),
            (1,1),(5,1),
            (0,2),
            (0,3),(5,3),
            (1,4),(2,4),(3,4),(4,4)
        ]
    },

    "HWSS": {
        "size": (7, 5),
        "cells": [
            (2,0),(3,0),(4,0),(5,0),
            (1,1),(6,1),
            (0,2),
            (0,3),(6,3),
            (1,4),(2,4),(3,4),(4,4),(5,4)
        ]
    },

    "Pulsar": {
        "size": (13, 13),
        "cells": [
            (2,0),(3,0),(4,0),(8,0),(9,0),(10,0),
            (0,2),(5,2),(7,2),(12,2),
            (0,3),(5,3),(7,3),(12,3),
            (0,4),(5,4),(7,4),(12,4),
            (2,5),(3,5),(4,5),(8,5),(9,5),(10,5),
            (2,7),(3,7),(4,7),(8,7),(9,7),(10,7),
            (0,8),(5,8),(7,8),(12,8),
            (0,9),(5,9),(7,9),(12,9),
            (0,10),(5,10),(7,10),(12,10),
            (2,12),(3,12),(4,12),(8,12),(9,12),(10,12)
        ]
    },

    "Pentadecathlon": {
        "size": (10, 3),
        "cells": [
            (1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0),(8,0),
            (0,1),(9,1),
            (1,2),(2,2),(3,2),(4,2),(5,2),(6,2),(7,2),(8,2)
        ]
    },

    "Rpent": {
        "size": (3, 3),
        "cells": [
            (1,0),(2,0),
            (0,1),(1,1),
            (1,2)
        ]
    },

    "Acorn": {
        "size": (7, 3),
        "cells": [
            (1,0),
            (3,1),
            (0,2),(1,2),(4,2),(5,2),(6,2)
        ]
    },

    "Diehard": {
        "size": (8, 3),
        "cells": [
            (6,0),
            (0,1),(1,1),
            (1,2),(5,2),(6,2),(7,2)
        ]
    }
}

def generate_full_array(name, width, height, sparse):
    grid = [[0 for _ in range(width)] for _ in range(height)]
    for x, y in sparse:
        grid[y][x] = 1

    print(f"// {name} ({width}x{height})")
    print(f"static const uint8_t {name.lower()}_cells[] = {{")
    for row in grid:
        print("    " + ",".join(str(v) for v in row) + ",")
    print("};\n")


def main():
    for name, data in structures.items():
        width, height = data["size"]
        sparse = data["cells"]
        generate_full_array(name, width, height, sparse)

    print("// Add these to structures_list:")
    for name, data in structures.items():
        width, height = data["size"]
        print(f'    {{ "{name}", {width}, {height}, {name.lower()}_cells }},')

if __name__ == "__main__":
    main()