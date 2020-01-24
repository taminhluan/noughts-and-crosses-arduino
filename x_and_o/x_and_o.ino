#define BOARD_SIZE  50

/*
 * @author: luantm
 * Board: with BOARD_SIZE x BOARD_SIZE
 * cell value: _, x, o
 */
char board[BOARD_SIZE][BOARD_SIZE];

// check win
// return 1: win
// return 0: no win
// return -1: lose 
char checkState(char board[][]);

// de quy
void minimax();

// draw board
void drawBoard(char board[][]);

// nhap du lieu tu nguoi dung
void input();

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
}
