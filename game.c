#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "draw_board.h"
#include <stdlib.h>
#include <string.h>
#include "piece.h"
#include <time.h>

#define START_SCREEN_WIDTH 500
#define START_SCREEN_HEIGHT 500

// struct current_piece {
//     int x;
//     int y;
//     int grid[5][5];
//     int rotation;
//     int placed;
// };

void playGame(int boardPosition[21][12]);
void addPiece(int (*boardPosition)[12], struct current_piece);
void removePiece(int (*boardPosition)[12], struct current_piece);
void getInput(struct current_piece*, int boardPosition[21][12]);
void turnRight(struct current_piece*);
void turnLeft(struct current_piece*);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);



int main(){

    srand(time(NULL));

    // start window
    InitWindow(START_SCREEN_WIDTH, START_SCREEN_HEIGHT,"Tetris");
    SetWindowMinSize(100,100);
    SetWindowMaxSize(1000,1000);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    struct current_piece piece;

    piece.placed = 1;

    int boardPosition[21][12] = {
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    };
    

    struct game_stats game = {0, {0,1,2,3,4,5,6}};

    // Game loop
    while (!WindowShouldClose()){
        newPiece(&piece, &game);
        getInput(&piece, boardPosition);
        addPiece(boardPosition, piece);
        playGame(boardPosition);
        removePiece(boardPosition, piece);
    }
    CloseWindow();

    return 0;
}


void playGame(int boardPosition[21][12]){

    //Board Dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    struct board board = getBoardDimensions(screenWidth, screenHeight);


    // Tester Board Position
    

    // Draw Screen
    BeginDrawing();
    ClearBackground(BLACK);

    drawBoard(board);
    drawPosition(boardPosition, board);



    EndDrawing();
}

void addPiece(int (*boardPosition)[12], struct current_piece piece){

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece.grid[i][j] == 0){
                continue;
            }
            boardPosition[i+piece.y][j+piece.x] = piece.grid[i][j];
        }
    }
}

void removePiece(int (*boardPosition)[12], struct current_piece piece){

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece.grid[i][j] == 0){
                continue;
            }
            boardPosition[i+piece.y][j+piece.x] = 0;
        }
    }
}



void getInput(struct current_piece* piece, int boardPosition[21][12]){

    struct current_piece copy;

    if (IsKeyPressed(KEY_K)){
        copyPiece(&copy, piece);
        turnRight(&copy);
        if (collisionCheck(copy, boardPosition) == 0){
            turnRight(piece);
        }
    }

    if (IsKeyPressed(KEY_J)){
        copyPiece(&copy, piece);
        turnLeft(&copy);
        if (collisionCheck(copy, boardPosition) == 0){
            turnLeft(piece);
        }
    }

    if (IsKeyPressed(KEY_SPACE)){
        piece->placed = 1;
        piece->x = 3;
        piece->y = 0;
    }

    if (IsKeyPressed(KEY_D)){
        changeX(piece, 1, boardPosition);
    }

    if (IsKeyPressed(KEY_A)){
        changeX(piece, -1, boardPosition);
    }
}



