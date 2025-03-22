struct current_piece {
    int x;
    int y;
    int grid[5][5];
    int rotation;
    int placed;
};

void newPiece(struct current_piece* piece);
void changeX(struct current_piece* piece, int direction, int boardPosition[21][12]);