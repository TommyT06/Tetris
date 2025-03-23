#ifndef STRUCT_H
#define STRUCT_H

struct current_piece {
    int x;
    int y;
    int grid[5][5];
    int rotation;
    int placed;
    int type;
};

#endif