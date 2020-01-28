//
//  main.c
//  noughts_and_crosses
//
//  Created by Luan Ta on 1/26/20.
//  Copyright © 2020 Ta Minh Luan. All rights reserved.
//
#define BOARD_SIZE          15
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
/*
 * iStep, jStep - direction: (-1, -1), (1, 0) ...
 */
char checkWinWithDirection(char i, char j, char iStep, char jStep);

char checkLegalMove(char i, char j);

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
    for (char i = 0; i < BOARD_SIZE; i ++ ) {
        for (char j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != CHARACTER_DEFAULT) {
                for (char iStep = -1; iStep <= 1; iStep++) {
                    for (char jStep = -1; jStep <= 1; jStep ++)
                    {
                        char isWin = checkWinWithDirection(i, j, iStep, jStep);
                        if (isWin) {
                            return board[i][j];
                        } else {
                            continue;
                        }
                    }
                }
            }
        }
    }
    
    
    
    return CHARACTER_DEFAULT;
}

/*
 * return 1: win
 * return 0: not win
 */
char checkWinWithDirection(char i, char j, char iStep, char jStep) {
    if (iStep == 0 && jStep == 0) return 0;
    if (!checkLegalMove(i + iStep*4, j + jStep*4) ) return 0;
    
    for (char step = 1; step <= 4; step++) {
        if (board[i][j] != board[i + iStep*step][j + step*jStep] ) {
            return 0;
        }
    }
    
    // check stuck at begin and end
    if (checkLegalMove(i - 1 * iStep, j - 1 * jStep)) {
        if (board[i - 1 * iStep][j - 1 * jStep] != CHARACTER_DEFAULT) {
            if (checkLegalMove(i + 5 * iStep, j + 5 * jStep)) {
                if (board[i - 1 * iStep][j - 1 * jStep] != CHARACTER_DEFAULT) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/*
 * return 1: legal move
 * return 0:
 */
char checkLegalMove(char i, char j) {
    if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
        return 1;
    } else {
        return 0;
    }
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
