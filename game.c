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

#define START_SCREEN_WIDTH 1000
#define START_SCREEN_HEIGHT 1000

void renderScreen(int boardPosition[23][12], struct game_stats, struct current_piece);
void playGame(void);
void addPiece(int (*boardPosition)[12], struct current_piece*);
void removePiece(int (*boardPosition)[12], struct current_piece*);
int getInput(struct current_piece*, struct current_piece*,  int boardPosition[23][12], struct game_stats*, struct current_piece*);
void turnRight(struct current_piece*);
void turnLeft(struct current_piece*);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);
void changeGhost(int (*boardPosition)[12], struct current_piece* piece);
void clearLines(int (*boardPosition)[12], int);
int deleteLines(int (*boardPosition)[12]);



double heldInputStartTime = 0;
double lastChange = 0;

int pieceNotMoved = 0;
double lastTimeMoved = 0;

int usedHoldYetEver = 0;
int HoldUsedYetThisGo = 0;

int main(){

    // start window
    InitWindow(START_SCREEN_WIDTH, START_SCREEN_HEIGHT,"Tetris");
    // SetWindowMinSize(100,100);
    // SetWindowMaxSize(1000,1000);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    SetTargetFPS(60);

    int Quit_Game = 0;

    playGame();
    // Game loop
    while (Quit_Game == 0 && !WindowShouldClose()){
        int playAgain = 0;
        printf("Play Again: ");
        scanf("%d", &playAgain);
        if (playAgain == 0){
            Quit_Game = 1;
        }
        if (playAgain == 1){
            while (GetKeyPressed() != 0);
            playGame();
        }
    }
    CloseWindow();

    return 0;
}

void playGame(){


    heldInputStartTime = 0;
    lastChange = 0;

    pieceNotMoved = 0;
    lastTimeMoved = 0;

    usedHoldYetEver = 0;
    HoldUsedYetThisGo = 0;


    double lastDropTime = 0;
    double dropDelay = 1;
    // default stats for game start
    struct current_piece piece;
    struct current_piece ghost;
    struct current_piece hold;

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
    

    struct game_stats game = {0, {0,1,2,3,4,5,6}, {0,1,2,3,4,5,6}, 0, 1};

    shuffle(game.piece_order, 7);
    shuffle(game.piece_order2, 7);

    newPiece(&piece, &game);

    int gameOver = 0;
    while (gameOver == 0 && !WindowShouldClose()){

        if (game.linesCleared / 10 >= game.level){
            game.level++;
            dropDelay = pow((0.8 - ((game.level-1)*0.007)),(game.level-1));
            // printf("%f %d", dropDelay, game.linesCleared);
            // fflush(stdout);
        }

        //addPiece(boardPosition, &piece);
        double currentTime = GetTime();
        if ((currentTime - lastDropTime >= dropDelay) && piece.y < ghost.y){
            lastDropTime = currentTime;
            piece.y++;
        }

        int changeGhostColourCheck = getInput(&piece, &ghost, boardPosition, &game, &hold);
        
        ghost = piece;

        copyMatrix(ghost.grid, piece.grid);

        getGhost(&ghost, boardPosition);
        
        addPiece(boardPosition, &ghost);

        if (ghost.y == piece.y){
            if (pieceNotMoved == 0){
                lastTimeMoved = GetTime();
                pieceNotMoved = 1;
            }
            if (pieceNotMoved == 1){
                if (currentTime - lastTimeMoved >= 0.5){
                    changeGhostColourCheck = 1;
                    pieceNotMoved = 0;
                }
            }
        }

        if (changeGhostColourCheck == 1){
            piece.placed = 1;
            pieceNotMoved = 0;
            HoldUsedYetThisGo = 0;
            //removePiece(boardPosition, &piece);
            changeGhost(boardPosition, &piece);
            newPiece(&piece, &game);
            if (collisionCheck(&piece, boardPosition)){
                gameOver = 1;
                ClearBackground(BLACK);
                renderScreen(boardPosition, game, hold);
                return;
            }
            game.linesCleared += deleteLines(boardPosition);
            
            renderScreen(boardPosition, game, hold);
        }
        //getInput(&piece, boardPosition, boardPosition, &game);
        else{
            addPiece(boardPosition, &piece);
            renderScreen(boardPosition, game, hold);
            removePiece(boardPosition, &piece);
            removePiece(boardPosition, &ghost);
        }

        // check for full lines

    }
}

void renderScreen(int boardPosition[23][12], struct game_stats game_stats, struct current_piece hold){

    //Board Dimensions
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    struct board board = getBoardDimensions(screenWidth, screenHeight);
    fflush(stdout);

    // Draw Screen
    BeginDrawing();
    ClearBackground(BLACK);

    drawBoard(board);
    drawPosition(boardPosition, board);
    drawScoreboard(board, game_stats);

    if (usedHoldYetEver == 1){
        
        DrawText("HOLD", board.x - (4 * getSquareSize()), board.y , 20, WHITE);
        drawSmallPiece(hold, board, board.x - (4 * getSquareSize()), board.y + (getSquareSize()));
    }

    drawPiecesUpNext(board, board.x + board.w + (getSquareSize()), board.y+ (getSquareSize()), game_stats);

    EndDrawing();
}

int getInput(struct current_piece* piece, struct current_piece* ghost, int boardPosition[23][12], struct game_stats* game, struct current_piece* hold){

    struct current_piece copy;

    if (IsKeyPressed(KEY_K)){
        copyPiece(&copy, piece);
        turnRight(&copy);
        if (collisionCheck(&copy, boardPosition) == 0){
            turnRight(piece);
            pieceNotMoved = 0;
        }
        return 0;
    }

    if (IsKeyPressed(KEY_H)){
        if (usedHoldYetEver == 0){
            usedHoldYetEver = 1;
            copyPiece(hold, piece);
            while (hold->rotation != 0){
                    turnRight(hold);
            }
            piece->placed = 1;
            newPiece(piece, game);
        }
        else {
            if (HoldUsedYetThisGo == 0){

                
                copyPiece(&copy, piece);
                copyPiece(piece, hold);
                copyPiece(hold, &copy);
                piece->y = -1;
                hold->y = -1;
                while (hold->rotation != 0){
                    turnRight(hold);
                }
                HoldUsedYetThisGo = 1;
            }
        }
    }

    if (IsKeyPressed(KEY_J)){
        copyPiece(&copy, piece);
        turnLeft(&copy);
        if (collisionCheck(&copy, boardPosition) == 0){
            turnLeft(piece);
            pieceNotMoved = 0;
        }
        return 0;
    }

    if (IsKeyPressed(KEY_SPACE)){
        return 1;
    }

    // Left
    if (IsKeyPressed(KEY_D)){
        int temp_x = piece->x;
        heldInputStartTime = GetTime();
        changeX(piece, 1, boardPosition);
        if (piece->x != temp_x){
            heldInputStartTime = GetTime();
            pieceNotMoved = 0;
        }
        return 0;
    }
    if (IsKeyDown(KEY_D)){
        double currentTime = GetTime();
        if (currentTime - heldInputStartTime >= 0.2 && (currentTime - lastChange > 0.075)){
            changeX(piece, 1, boardPosition);
            lastChange = currentTime;
        }
        return 0;
    }

    if (IsKeyReleased(KEY_D)){
        heldInputStartTime = GetTime();
        return 0;
    }

    // Right

    if (IsKeyPressed(KEY_A)){
        int temp_x = piece->x;
        heldInputStartTime = GetTime();
        changeX(piece, -1, boardPosition);
        if (piece->x != temp_x){
            heldInputStartTime = GetTime();
            pieceNotMoved = 0;
        }
    }
    if (IsKeyDown(KEY_A)){
        double currentTime = GetTime();
        if (currentTime - heldInputStartTime >= 0.2 && (currentTime - lastChange > 0.075)){
            changeX(piece, -1, boardPosition);
            lastChange = currentTime;
        }
        return 0;
    }
    if (IsKeyReleased(KEY_A)){
        heldInputStartTime = GetTime();
        return 0;
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
            
            return 1 + deleteLines(boardPostition);
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