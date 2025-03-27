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

struct board {
    int x;
    int y;
    int w;
    int h;
};

struct game_stats {
    int piece_count;
    int piece_order[7];
    int piece_order2[7];
    int linesCleared;
    int level;
};

#endif