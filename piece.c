#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct current_piece {
    int x;
    int y;
    int grid[5][5];
    int rotation;
    int placed;
};

void copyMatrix(int dest[5][5], int src[5][5]);
int collisionCheck(struct current_piece piece, int boardPosition[21][12]);
void changeX(struct current_piece* piece, int direction, int boardPosition[21][12]);

int I_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int J_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 3, 0, 0, 0},
    {0, 3, 3, 3, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int L_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 4, 0},
    {0, 4, 4, 4, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int O_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 2, 2, 0},
    {0, 0, 2, 2, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int S_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 5, 5, 0},
    {0, 5, 5, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int T_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 7, 0, 0},
    {0, 7, 7, 7, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

int Z_piece[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 6, 6, 0, 0},
    {0, 0, 6, 6, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

void newPiece(struct current_piece* piece){

    if (piece->placed == 1){
        piece->x = 4;
        piece->y = 0;
        piece->placed = 0;
        piece->rotation = 0;

        int randomPiece = rand() % 7;
        switch (randomPiece){
            case 0:
            copyMatrix(piece->grid, I_piece);
            break;
            case 1:
            copyMatrix(piece->grid, O_piece);
            break;
            case 2:
            copyMatrix(piece->grid, Z_piece);
            break;
            case 3:
            copyMatrix(piece->grid, S_piece);
            break;
            case 4:
            copyMatrix(piece->grid, T_piece);
            break;
            case 5:
            copyMatrix(piece->grid, L_piece);
            break;
            case 6:
            copyMatrix(piece->grid, J_piece);
            break;
        }
    }
}

void copyMatrix(int dest[5][5], int src[5][5]){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            dest[i][j] = src[i][j];
        }
    }
}

void changeX(struct current_piece* piece, int direction, int boardPosition[21][12]){

    struct current_piece piece_check;
    piece_check.x = (piece->x) + direction;
    piece_check.y = piece->y;
    copyMatrix(piece_check.grid, piece->grid);

    int collision = collisionCheck(piece_check, boardPosition);

    if (collision == 0){
        piece->x = piece->x + direction;
    }
}

int collisionCheck(struct current_piece piece, int boardPosition[21][12]){
  
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece.grid[i][j] != 0){
                if (boardPosition[piece.y+i][piece.x+j] != 0){
                    return 1;
                }
            }
        }
    }

    return 0;
}