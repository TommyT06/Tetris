struct board {
    int x;
    int y;
    int w;
    int h;
};
void drawBoard(struct board board);
void drawPosition(int boardPosition[20][10], struct board board);
struct board getBoardDimensions(int, int);
struct Color getSquareColor(int block);
int getSquareSize(void);


