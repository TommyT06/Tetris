struct current_piece {
    int x;
    int y;
    int grid[5][5];
    int rotation;
    int placed;
    int type;
};
struct game_stats {
    int piece_count;
    int piece_order[7];
};

void newPiece(struct current_piece* piece, struct game_stats*);
void changeX(struct current_piece* piece, int direction, int boardPosition[21][12]);
void copyMatrix(int dest[5][5], int src[5][5]);
int collisionCheck(struct current_piece piece, int boardPosition[21][12]);
void turnRight(struct current_piece* piece);
void turnLeft(struct current_piece* piece);
void copyPiece(struct current_piece* dest_piece, struct current_piece* src_piece);