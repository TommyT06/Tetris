#include "piece.h"
#include "draw_board.h"
#include "struct.h"
#include <stdio.h>

int lookUp(int boardPosition[23][12], struct current_piece* piece, int y, int starter_y){

    int temp_y = piece->y;

    while (y > 0 && y >= starter_y){
        y--;
        piece->y = y;

        if (collisionCheck(piece, boardPosition) == 1){
            piece->y = temp_y;
            return 0;
        }
    }

    piece->y = temp_y;
    return 1;

}



void getGhost(struct current_piece* piece, int boardPosition[23][12]){

    // for (int i = 0; i < 23; i++){
    //     for (int j = 0; j < 12; j++){
    //         printf("%d ", boardPosition[i][j]);
    //     }
    //     printf("\n");
    // }

    // fflush(stdout);


    int starter_y = piece->y;

    piece->y = 10;

    for (int i = 19; i >= 0; i--){
        piece->y = i;
        if ((lookUp(boardPosition, piece, i, starter_y) == 1) && (collisionCheck(piece, boardPosition) == 0) && (i >= starter_y)){
            break;
        }
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece->grid[i][j] != 0){
                piece->grid[i][j] = 8;
            }
        }
    }

}