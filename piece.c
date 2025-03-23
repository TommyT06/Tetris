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

struct game_stats {
    int piece_count;
    int piece_order[7];
};
void copyMatrix(int dest[5][5], int src[5][5]);
int collisionCheck(struct current_piece piece, int boardPosition[21][12]);
void changeX(struct current_piece* piece, int direction, int boardPosition[21][12]);
void shuffle(int arr[], int size);
void turnLeft(struct current_piece* piece);
void turnRight(struct current_piece* piece);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);

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

int gen_offset[4][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,-1,0,2,1,2},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,-1,0,-1,-1,0,2,-1,2},
};

int i_offset[4][10] = {
    {0,0,-1,0,2,0,-1,0,2,0},
    {-1,0,0,0,0,0,0,1,0,-2},
    {-1,1,1,1,-2,1,1,0,-1,0},
    {0,1,0,1,0,1,0,-1,0,2}
};

int o_offset[4][2] ={
    {0,0},
    {0,-1},
    {-1,-1},
    {-1,0}
};

void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Random index from 0 to i
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


void newPiece(struct current_piece* piece, struct game_stats* game){

    if (game->piece_count == 7){
        game->piece_count = 0;
        shuffle(game->piece_order,7);
    }

    if (piece->placed == 1){
        piece->x = 3;
        piece->y = 0;
        piece->placed = 0;
        piece->rotation = 0;

        int randomPiece = game->piece_order[game->piece_count];
        game->piece_count++;
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

void turnRight(struct current_piece* piece){


    // Transpose the matrix
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            int temp = piece->grid[i][j];
            piece->grid[i][j] = piece->grid[j][i];
            piece->grid[j][i] = temp;
        }
    }
    // Reverse each row
    for (int i = 0; i < 5; i++) {
        for (int j = 0, k = 5 - 1; j < k; j++, k--) {
            int temp = piece->grid[i][j];
            piece->grid[i][j] = piece->grid[i][k];
            piece->grid[i][k] = temp;
        }
    }

    piece->rotation = (piece->rotation + 1) % 4;
}

void turnLeft(struct current_piece* piece) {

    // Transpose the matrix
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            int temp = piece->grid[i][j];
            piece->grid[i][j] = piece->grid[j][i];
            piece->grid[j][i] = temp;
        }
    }

    // Reverse each column
    for (int j = 0; j < 5; j++) {
        for (int i = 0, k = 5 - 1; i < k; i++, k--) {
            int temp = piece->grid[i][j];
            piece->grid[i][j] = piece->grid[k][j];
            piece->grid[k][j] = temp;
        }
    }

    piece->rotation = (piece->rotation -1) % 4;
}


void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece){

    copyMatrix(dest_piece->grid, src_piece->grid);
    dest_piece->rotation = src_piece->rotation;
    dest_piece->x = src_piece->x;
    dest_piece->y = src_piece->y;
    dest_piece->rotation = src_piece->rotation;

}