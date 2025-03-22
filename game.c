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
    

    // Game loop
    while (!WindowShouldClose()){
        newPiece(&piece);
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

    if (IsKeyPressed(KEY_K)){
        turnRight(piece);
    }

    if (IsKeyPressed(KEY_J)){
        turnLeft(piece);
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



void turnRight(struct current_piece* piece){

    piece->rotation = (piece->rotation + 1) % 4;
    printf("%d", piece->rotation);

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
}

void turnLeft(struct current_piece* piece) {

    piece->rotation = (piece->rotation -1) % 4; 
    printf("%d", piece->rotation);

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
}


