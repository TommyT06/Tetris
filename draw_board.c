#include "raylib.h"
#include <math.h>

struct board {
    int x;
    int y;
    int w;
    int h;
};

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

        case 7:
        color = PURPLE;
        break;

        default:
        color = BLACK;
        break;
    }

    return color;
}

void drawPosition(int boardPosition[20][10], struct board board){
    
    struct Square {
        int x;
        int y;
    };

    struct Square square;
    int squareSize = getSquareSize();

    for (int i = 19; i >= 0; i--){
        for ( int j = 0; j < 10; j++){

            if (boardPosition[i][j] != 0){
                square.x = board.x + (j * squareSize);
                square.y = board.y + (i * squareSize);
                struct Color color = getSquareColor(boardPosition[i][j]);
                DrawRectangleGradientV(square.x, square.y, squareSize,squareSize, color, WHITE);
                DrawRectangleLines(square.x, square.y, squareSize,squareSize, BLACK);
            }
        }
    }
}
