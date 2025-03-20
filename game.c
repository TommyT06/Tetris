#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

int main(){

    InitWindow(100,100,"Tetris");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hey", 50,50,5,DARKBLUE);
        EndDrawing();
    }
    CloseWindow();



}