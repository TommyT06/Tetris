#include "raylib.h"
#include <math.h>
#include "piece.h"
#include "struct.h"
#include "stdio.h"
#include "string.h"

int getSquareSize(void){

    int screenHeight = GetScreenHeight();
    // board height shoudl be 80% of screen height
    int board_height = screenHeight * 0.8;
    // 20 squares on board so div by 20 for square size
    int square_size = floor(board_height / 20);

    return square_size;
}

void drawBoard(struct board board){

    // Board is 10 * 20 squares
    struct Rectangle board_outline = {board.x-2, board.y-2, board.w+4, board.h+4};

    DrawRectangleLinesEx(board_outline, 2, WHITE);

}

struct board getBoardDimensions(int screenWidth, int screenHeight){

    struct board board;

    int squareSize = getSquareSize();
    board.h = 20 * squareSize;
    board.w = 10 * squareSize;

    board.x = floor((screenWidth - board.w) / 2);
    board.y = floor((screenHeight - board.h) / 2);

    return board;
}

struct Color getSquareColor(int block){

    struct Color color;

    switch (block){
        // block I
        case 1:
        color = (Color){0, 255,255,255};
        break;

        // block O
        case 2:
        color = YELLOW;
        break;

        // block J
        case 3:
        color = BLUE;
        break;

        // block L
        case 4:
        color = ORANGE;
        break;

        // block s
        case 5:
        color = GREEN;
        break;

        // block Z
        case 6:
        color = RED;
        break;

        // block T
        case 7:
        color = PURPLE;
        break;

        case 8:
        color = WHITE;
        break;

        default:
        color = BLACK;
        break;
    }

    return color;
}

void drawPosition(int boardPosition[23][12], struct board board){
    
    // for (int i =0; i < 21; i++){
    //     for (int j = 0; j < 12; j++){
    //         printf("%d ", boardPosition[i][j]);
    //     }
    //     printf("\n");
    // }
    fflush(stdout);

    struct Square {
        int x;
        int y;
    };

    struct Square square;
    int squareSize = getSquareSize();

    for (int i = 21; i >= 2; i--){
        for ( int j = 1; j < 11; j++){

            if (boardPosition[i][j] != 0){
                square.x = board.x + ((j-1)* squareSize);
                square.y = board.y + ((i-2) * squareSize);
                struct Color color = getSquareColor(boardPosition[i][j]);
                DrawRectangle(square.x, square.y, squareSize,squareSize, color);
            }
        }
    }
}

void drawScoreboard(struct board board, struct game_stats game){

    int level_x = board.x / 2;
    int level_y = board.h * 0.5;

    int lines_x = board.x / 2;
    int lines_y = board.h * 0.7;

    char lines[30] = "Lines Cleared: ";
    char buf[10];

    snprintf(buf, 10, "%d", game.linesCleared);

    strcat(lines, buf);

    DrawText(lines, lines_x, lines_y, 30, WHITE);

    char level[30] = "Level: ";
    char buffer[10];

    snprintf(buffer, 10, "%d", game.level);

    strcat(level, buffer);

    DrawText(level, level_x, level_y, 30, WHITE);

}

void drawSmallPiece(struct current_piece piece, struct board board, int x, int y){

    struct square {
        int x;
        int y;
    };

    struct square square;

    int squareSize = (getSquareSize()) * 0.75;

    for (int i = 4; i >= 0; i--){
        for ( int j = 0; j < 5; j++){

            if (piece.grid[i][j] != 0){
                square.x = x + ((j)* squareSize);
                square.y = y + ((i) * squareSize);
                struct Color color = getSquareColor(piece.grid[i][j]);
                DrawRectangle(square.x, square.y, squareSize,squareSize, color);
            }
        }
    }

}

void drawPiecesUpNext(struct board board, int x, int y, struct game_stats game){

    struct current_piece piece;
    piece.placed = 1;

    for (int i = 0; i < 7; i++){
        newPiece(&piece, &game);
        piece.placed = 1;
        drawSmallPiece(piece, board, x, y + ((getSquareSize() * 3)*i));
    }

}


