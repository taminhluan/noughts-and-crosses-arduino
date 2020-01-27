//
//  main.c
//  noughts_and_crosses
//
//  Created by Luan Ta on 1/26/20.
//  Copyright © 2020 Ta Minh Luan. All rights reserved.
//
#define BOARD_SIZE          20
#define CHARACTER_DEFAULT   ' '
#define CHARACTER_CROSS     'x'
#define CHARACTER_NOUGHT    'o'
#include <stdio.h>

char board[BOARD_SIZE][BOARD_SIZE];

enum STEP {
    HUMAN,
    AI
};

char currentStep = HUMAN;

void initBoard(void);
void drawBoard(char board[BOARD_SIZE][BOARD_SIZE]);

void humanInput(void);
void aiInput(void);
char checkWin(void);

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

void humanInput() {
    printf("\nHUMAN (%c): x y: \n", CHARACTER_NOUGHT);
    int x, y;
    do {
//        TODO try catch
        scanf("%d %d", &x, &y);
    } while (board[x][y] != CHARACTER_DEFAULT);
    
    board[x][y] = CHARACTER_NOUGHT; //Fix hardcode in here
}

void aiInput() {
//    calculate();
    printf("\nAI (%c): x y \n", CHARACTER_CROSS);
    
}

/*
 * return CHARACTER_...
 */
char checkWin() {
    for (int i = 0; i < BOARD_SIZE - 4; i ++) {
        for (int j = 0; j < BOARD_SIZE - 4; j ++) {
            if (board[i][j] == CHARACTER_DEFAULT) {
                continue;
            }
            
            if (
                (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4])
                || (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j])
                || (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4])
                )
            {
                return board[i][j];
            }
        }
    }
    return CHARACTER_DEFAULT;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Welcome to play noughts and crosses!\n");
    initBoard();
    
    drawBoard(board);
    
    while (1) {
        if (currentStep == HUMAN) {
            humanInput();
            currentStep = AI;
        } else {
            aiInput();
            currentStep = HUMAN;
        }
        
        drawBoard(board);
        
        char winner = checkWin();
        
        if (winner == CHARACTER_NOUGHT) {
            printf("\nHUMAN(%c) Win\n", CHARACTER_NOUGHT);
            break;
        } else if (winner == CHARACTER_CROSS) {
            printf("\nAI(%c) win\n", CHARACTER_CROSS);
            break;
        }
        
    }
    return 0;
}
