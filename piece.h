#ifndef PIECE_H
#define PIECE_H

#include "struct.h"


void newPiece(struct current_piece* piece, struct game_stats*);
void changeX(struct current_piece* piece, int direction, int boardPosition[23][12]);
void copyMatrix(int dest[5][5], int src[5][5]);
int collisionCheck(struct current_piece* piece, int boardPosition[23][12]);
void turnRight(struct current_piece* piece);
void turnLeft(struct current_piece* piece);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);
void shuffle(int arr[], int size);
#endif