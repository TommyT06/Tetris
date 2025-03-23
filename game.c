#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "draw_board.h"
#include <stdlib.h>
#include <string.h>
#include "piece.h"
#include <time.h>
#include "ghost.h"
#include "struct.h"
#include <unistd.h>

#define START_SCREEN_WIDTH 500
#define START_SCREEN_HEIGHT 500

// struct current_piece {
//     int x;
//     int y;
//     int grid[5][5];
//     int rotation;
//     int placed;
// };

void playGame(int boardPosition[23][12]);
void addPiece(int (*boardPosition)[12], struct current_piece*);
void removePiece(int (*boardPosition)[12], struct current_piece*);
int getInput(struct current_piece*, struct current_piece*,  int boardPosition[23][12], struct game_stats*);
void turnRight(struct current_piece*);
void turnLeft(struct current_piece*);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);
void changeGhost(int (*boardPosition)[12], struct current_piece* piece);
void clearLines(int (*boardPosition)[12], int);
int deleteLines(int (*boardPosition)[12]);

double lastDropTime = 0;
double dropDelay = 0.5;

int main(){

    srand(time(NULL));

    // start window
    InitWindow(START_SCREEN_WIDTH, START_SCREEN_HEIGHT,"Tetris");
    SetWindowMinSize(100,100);
    SetWindowMaxSize(1000,1000);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    struct current_piece piece;
    struct current_piece ghost;

    piece.placed = 1;

    int boardPosition[23][12] = {
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
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    };
    

    struct game_stats game = {0, {0,1,2,3,4,5,6}};

    newPiece(&piece, &game);
    // Game loop
    while (!WindowShouldClose()){
        //newPiece(&piece, &game);
        //getInput(&piece, boardPosition, boardPosition);

        int changeGhostColourCheck = getInput(&piece, &ghost, boardPosition, &game);
        
        ghost = piece;
        copyMatrix(ghost.grid, piece.grid);

        getGhost(&ghost, boardPosition);
        
        addPiece(boardPosition, &ghost);

        

        //addPiece(boardPosition, &piece);
        double currentTime = GetTime();
        if ((currentTime - lastDropTime >= dropDelay) && piece.y != ghost.y){
            lastDropTime = currentTime;
            piece.y++;
        }

        if (changeGhostColourCheck == 1){
            piece.placed = 1;
            //removePiece(boardPosition, &piece);
            changeGhost(boardPosition, &piece);
            newPiece(&piece, &game);
            playGame(boardPosition);
        }
        //getInput(&piece, boardPosition, boardPosition, &game);
        else{
            addPiece(boardPosition, &piece);
            playGame(boardPosition);

            


            removePiece(boardPosition, &piece);
            removePiece(boardPosition, &ghost);
        }
        deleteLines(boardPosition);

    }
    CloseWindow();

    return 0;
}


void playGame(int boardPosition[23][12]){

    //Board Dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    struct board board = getBoardDimensions(screenWidth, screenHeight);

    for (int i = 0; i < 23; i++){
        for (int j = 0; j < 12; j++){
            printf("%d ", boardPosition[i][j]);
        }
        printf("\n");
    }

    fflush(stdout);

    // Tester Board Position
    

    // Draw Screen
    BeginDrawing();
    ClearBackground(BLACK);

    drawBoard(board);
    drawPosition(boardPosition, board);

    EndDrawing();
}

int getInput(struct current_piece* piece, struct current_piece* ghost, int boardPosition[23][12], struct game_stats* game){

    struct current_piece copy;

    if (IsKeyPressed(KEY_K)){
        copyPiece(&copy, piece);
        turnRight(&copy);
        if (collisionCheck(&copy, boardPosition) == 0){
            turnRight(piece);
        }
    }

    if (IsKeyPressed(KEY_J)){
        copyPiece(&copy, piece);
        turnLeft(&copy);
        if (collisionCheck(&copy, boardPosition) == 0){
            turnLeft(piece);
        }
    }

    if (IsKeyPressed(KEY_SPACE)){
        return 1;
    }

    if (IsKeyPressed(KEY_D)){
        changeX(piece, 1, boardPosition);
    }

    if (IsKeyPressed(KEY_A)){
        changeX(piece, -1, boardPosition);
    }

    return 0;
}

void addPiece(int (*boardPosition)[12], struct current_piece* piece){

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece->grid[i][j] == 0){
                continue;
            }
            boardPosition[i+piece->y][j+piece->x] = piece->grid[i][j];
        }
    }
}

void removePiece(int (*boardPosition)[12], struct current_piece* piece){

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (piece->grid[i][j] == 0){
                continue;
            }
            boardPosition[i+piece->y][j+piece->x] = 0;
        }
    }
}

void changeGhost(int (*boardPosition)[12], struct current_piece* piece){

    for (int i = 2; i < 23; i++){
        for (int j = 0; j < 12; j++){
            if (boardPosition[i][j] == 8){
                boardPosition[i][j] = piece->grid[2][2];
            }
        }
    }

}

int deleteLines(int (*boardPostition)[12]){

    int full = 1;
    int clearUpTo;

    for (int i = 0; i < 22; i++){
        full = 1;
        for (int j = 1; j < 11; j++){
            if (boardPostition[i][j] == 0){
                full = 0;
                break;
            }
        }
        if (full == 1){
            clearUpTo = i;
            clearLines(boardPostition, clearUpTo);
            return deleteLines(boardPostition);
        }
    }

    return 0;
}

void clearLines(int (*boardPosition)[12], int clearUpTo){

    for (int j = 0; j < 11; j++){
        for (int i = clearUpTo; i > 0; i--){
            boardPosition[i][j] = boardPosition[i-1][j];
        }
    }
}