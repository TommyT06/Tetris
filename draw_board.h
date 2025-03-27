#ifndef DRAW_BOARD_H
#define DRAW_BOARD_H

#include "struct.h"

void drawBoard(struct board board);
void drawPosition(int boardPosition[23][12], struct board);
struct board getBoardDimensions(int, int);
struct Color getSquareColor(int block);
int getSquareSize(void);
void drawScoreboard(struct board, struct game_stats);
void drawSmallPiece(struct current_piece piece, struct board board, int x, int y);
void drawPiecesUpNext(struct board board, int x, int y, struct game_stats game);

#endif
