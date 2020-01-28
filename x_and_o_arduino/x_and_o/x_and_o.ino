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

struct point {
    char x;
    char y;
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

struct point getBestMove(void);
int calculateScore(char currentCharacter); //return maxScore
int calculateScoreWithDirection(char currentCharacter, char i, char j, char iStep, char jStep);
char hasNeighbors(char currentCharacter, char i, char j);

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
        printf ("| %d", i);
        printf("|\n");
    }
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf(" %d", j % 10);
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
    printf("\nAI (%c): x y \n", CHARACTER_CROSS);
    
    struct point bestMove = getBestMove();
    
    board[bestMove.x][bestMove.y] = CHARACTER_CROSS;
    
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

int defendScoreBoard[BOARD_SIZE][BOARD_SIZE];
int maxDefendScore = 0;

int attackScoreBoard[BOARD_SIZE][BOARD_SIZE];
int maxAttackScore = 0;



/*
 * pattern '_____'
 * pattern '_oo|#' => '_oo##' => score = 143
 * pattern '_oox#' => '_####'=> score = 1
 */


int calculateScoreWithDirection(char currentCharacter, char i, char j, char iStep, char jStep) {
    
    char pattern[5] = { '#', '#', '#', '#', '#'};
    for (int step = 1; step <= 5; step ++) {
        char iCurrent = i + step * iStep;
        char jCurrent = j + step * jStep;
        if (checkLegalMove(iCurrent, jCurrent)) {
            
            if (board[iCurrent][jCurrent] == CHARACTER_DEFAULT) { // if this is no item
                pattern[step] = '_';
                continue;
            }
            
            if (board[iCurrent][jCurrent] == currentCharacter) { // if this is current character
                pattern[step] = 'o';
            } else { // else
                
                for (int rollback = step; rollback >= 1; rollback --) {
                    if (pattern[rollback] == 'o') {
                        pattern[rollback] = '#';
                    } else {
                        break;
                    }
                }
                break;
            }
        } else {
            // from here every character of pattern = '#'
            break;
        }
    }
    
    int score = 0;
    for (char indexOfPattern = 0; indexOfPattern < 5; indexOfPattern ++) {
        switch (pattern[indexOfPattern]) {
            case '_':
                score = score * 10 + 1;
                break;
            case 'o':
                score = score * 10 + 5;
            default:
                score = score * 10 + 0;
        }
    }
    return score;
}

char hasNeighbors(char currentCharacter, char i, char j) {
    for (int m = -1; m <= 1; m++) {
        for (int n = -1; n <= 1; n++) {
            if (m == 0 && n == 0) continue;
            
            if (currentCharacter == board[m + i][n + j]) return 1;
        }
    }
    
    return 0;
}

int calculateScore(char currentCharacter) {
    int maxScore = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {

            if (board[i][j] != CHARACTER_DEFAULT) {
                if (currentCharacter == CHARACTER_NOUGHT ) {
                    defendScoreBoard[i][j] = -1;
                    continue;
                } else {
                    attackScoreBoard[i][j] = -1;
                    continue;
                }
                
            }
            if (! hasNeighbors(currentCharacter ,i, j)) {
                if (currentCharacter == CHARACTER_NOUGHT ) {
                    defendScoreBoard[i][j] = 0;
                    continue;
                } else {
                    attackScoreBoard[i][j] = 0;
                    continue;
                }
            }
            
            int totalScore = 0;
            
            for (char iStep = - 1; iStep <=1; iStep ++) {
                for (char jStep = -1; jStep <= 1; jStep ++) {
                    if (iStep == 0 && jStep == 0) continue;
                    totalScore += calculateScoreWithDirection(currentCharacter, i, j, iStep, jStep);
                }
            }
            
            if (currentCharacter == CHARACTER_NOUGHT ) {
                defendScoreBoard[i][j] = totalScore;
            } else {
                attackScoreBoard[i][j] = totalScore;
            }
            
            if (maxScore < totalScore) {
                maxScore = totalScore;
            }
        }
    }
    return maxScore;
}


struct point getBestMove() {
    maxDefendScore = calculateScore(CHARACTER_NOUGHT);
    maxAttackScore = calculateScore(CHARACTER_CROSS);
    
    //for debug
    
    
    struct point result;
    
    result.x = 0;
    result.y = 0;
    
    if (maxDefendScore > maxAttackScore) { // defend
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (defendScoreBoard[i][j] == maxDefendScore) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
            }
        }
    } else {
        for (int i = 0; i < BOARD_SIZE; i++) { //attack
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (attackScoreBoard[i][j] == maxAttackScore) {
                    result.x = i;
                    result.y = j;
                    return result;
                }
            }
        }
    }
    
    return result;
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
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
  // put your main code here, to run repeatedly:

}
