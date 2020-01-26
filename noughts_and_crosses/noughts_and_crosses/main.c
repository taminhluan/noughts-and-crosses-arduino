//
//  main.c
//  noughts_and_crosses
//
//  Created by Luan Ta on 1/26/20.
//  Copyright © 2020 Ta Minh Luan. All rights reserved.
//
#define BOARD_SIZE          50
#define CHARACTER_DEFAULT   ' '
#define CHARACTER_CROSS     'x'
#define CHARACTER_NOUGHT    'o'
#include <stdio.h>

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard(void);
void drawBoard(char board[BOARD_SIZE][BOARD_SIZE]);

void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = CHARACTER_DEFAULT;
        }
    }
}

void drawBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Welcome to play noughts and crosses!\n");
    initBoard();
    
    board[0][0] = CHARACTER_CROSS;
    board[0][1] = CHARACTER_NOUGHT;
    drawBoard(board);
    return 0;
}
