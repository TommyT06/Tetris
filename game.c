#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "draw_board.h"

#define START_SCREEN_WIDTH 500
#define START_SCREEN_HEIGHT 500


void playGame(void);



int main(){


    // start window
    InitWindow(START_SCREEN_WIDTH, START_SCREEN_HEIGHT,"Tetris");
    SetWindowMinSize(100,100);
    SetWindowMaxSize(1000,1000);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Game loop
    while (!WindowShouldClose()){
        playGame();
    }
    CloseWindow();

    return 0;
}




void playGame(void){

    //Board Dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    struct board board = getBoardDimensions(screenWidth, screenHeight);


    // Tester Board Position
    int boardPosition[20][10] = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 7, 7, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}
    };

    // Draw Screen
    BeginDrawing();
    ClearBackground(BLACK);

    drawBoard(board);
    drawPosition(boardPosition, board);


    EndDrawing();
}