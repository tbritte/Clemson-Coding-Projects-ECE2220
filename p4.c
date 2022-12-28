/*  Tyrese Britten
    Systems Programming , Spring 2022
    Program 4
    FOr thsi project we are changing arrays and strings
    to make a game called 2048. We are making functions in 
    pass an array around called board to get the our 
    desired output
*/

// Libraries that was were used for this project
#include <stdio.h>

#include <string.h>

#include <stdbool.h>

#include <stdlib.h>

#include <assert.h>

#include <ctype.h>

#include <time.h>

//Gobal bool variable
bool played = false;

int highest_value_on_board(int board[4][4]){
    int highest_value_on_board = 0, i, j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if (highest_value_on_board < board[i][j]){
                highest_value_on_board = board[i][j];
            }
        }
    }
    return highest_value_on_board;
}

void print_board(int board[4][4], int score){  
    int i, j;
    int high_score = score;
    if (played) high_score = 100000;
    
    printf("*** Score = %d, High Score = %d *** \n", score, high_score);
    printf("Press Q if you want to quit. \n");
    for (i=0; i<4; i++){
        printf("-----------------------------\n");
        for (j=0; j<4; j++){
            if (board[i][j] != 0){
                printf("|%4d  ", board[i][j]);
            } else {
                printf("|      ");
            }
        }
        printf("|\n");
    } 
    printf("-----------------------------\n");
}

/* Generate function is generating 2's and 4's in empty spaces in the baord
array. 2's will spawn 90% of the time and 4's will spawn 10% of the time. The
spawn function will spawn the 2's and 4's in empty spaces on th board that have not filled 
up yet from doing other functions in the board arrow.*/
int generate_42() {
    srand(time(0));
    int randN = rand()%10;
    if (randN <= 8){
        return 2;
    } else {
        return 4;
    }
}
void spawn(int board[4][4]){
    bool empty = false;
    while(!empty){
        srand(time(0));
        int row = rand()%4;
        int col = rand()%4;
        if(board[row][col] == 0){
            board[row][col] = generate_42();
            empty = true;
        }
    }
}

/* Check functions for the different arrows keys are 
working as intended so there is not a bug with the 
board moving or arrow pressed on the keyboard */
int checkBelow(int board[4][4], int col, int row) {
    if (board[row][col] == 0 && row < 3) {
        return checkBelow(board, col, row+1);
    } else {
        int retVal = board[row][col];
        board[row][col] = 0;
        return retVal;
    } 
}
int checkUp(int board[4][4], int col, int row) {
    if (board[row][col] == 0 && row > 0) {
        return checkUp(board, col, row-1);
    } else {
        int retVal = board[row][col];
        board[row][col] = 0;
        return retVal;
    } 
}
int checkRight(int board[4][4], int col, int row) {
    if (board[row][col] == 0 && col < 3) {
        return checkRight(board, col+1, row);
    } else {
        int retVal = board[row][col];
        board[row][col] = 0;
        return retVal;
    } 
}
int checkLeft(int board[4][4], int col, int row) {
    if (board[row][col] == 0 && col > 0) {
        return checkLeft(board, col-1, row);
    } else {
        int retVal = board[row][col];
        board[row][col] = 0;
        return retVal;
    } 
}

/* Combine functions to combine the same numbers together
in order to score when the user press an arrow key. The numbers
will combine to ge add to each other to increase the value by +2.*/
int combineDoublesUp(int board[4][4], int score) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 3; row++) {
            if (board[row][col] == board[row+1][col]){
                score = score + board[row][col]*2;
                board[row][col] = board[row][col]*2;
                board[row+1][col] = 0;
            }
        }
    }
    return score;
}
int combineDoublesDown(int board[4][4], int score) {
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row > 0; row--) {
            if (board[row][col] == board[row-1][col]){
                score = score + board[row][col]*2;
                board[row][col] = board[row][col]*2;
                board[row-1][col] = 0;
            }
        }
    }
    return score;
}
int combineDoublesLeft(int board[4][4], int score) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == board[row][col+1]){
                score = score + board[row][col]*2;
                board[row][col] = board[row][col]*2;
                board[row][col+1] = 0;
            }
        }
    }
    return score;
}
int combineDoublesRight(int board[4][4], int score) {
    for (int row = 0; row < 4; row++) {
        for (int col = 4; col > 0; col--) {
            if (board[row][col] == board[row][col-1]){
                score = score + board[row][col]*2;
                board[row][col] = board[row][col]*2;
                board[row][col-1] = 0;
            }
        }
    }
    return score;
}

/* Move functions in moving the board when a user presses
an arrow key and hits enter. The numbers in the board will
all move left, right, up, and down to combine to one another.
If they don't they will fill up an empty space in the board
array*/
void moveUp(int board[4][4]) {
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            board[row][col] = checkBelow(board,col,row);
        }
    }
}
void moveDown(int board[4][4]) {
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row >= 0; row--) {
            board[row][col] = checkUp(board,col,row);
        }
    }
}
void moveLeft(int board[4][4]) {
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col++) {
            board[row][col] = checkRight(board,col,row);
        }
    }
}
void moveRight(int board[4][4]) {
     for (int row = 0; row < 4; row++) {
        for (int col = 3; col >= 0; col--) {
            board[row][col] = checkLeft(board,col,row);
        }
    }
}

/* Puts all the up, down, left and right functions into 
a press function to be used in arrows */
int pressedUp(int board[4][4], int score) {
    moveUp(board);
    score = combineDoublesUp(board, score);
    moveUp(board);
    return score;
}
int pressedDown(int board[4][4], int score) {
    moveDown(board);
    score = combineDoublesDown(board, score);
    moveDown(board);
    return score;
}
int pressedLeft(int board[4][4], int score) {
    moveLeft(board);
    score = combineDoublesLeft(board, score);
    moveLeft(board);
    return score;
}
int pressedRight(int board[4][4], int score) {
    moveRight(board);
    score = combineDoublesRight(board, score);
    moveRight(board);
    return score;
}

/* Arrows function to get the key arrows working with 
the board array. You will have to press the arrow then 
enter for it to work full as intended*/
int arrows(int board[4][4], int score){
    char input = getchar();
    if (input == '\033') {
        getchar();
        int value = getchar();
        fputs("\n", stdin);
    
        switch(value) { 
            case 'A':
                printf("Pressed Up\n");
                score = pressedUp(board, score);
                break;
            case 'B':
                printf("down\n");
                score = pressedDown(board, score);
                break;
            case 'C':
                printf("right\n");
                score = pressedRight(board, score);
                break;
            case 'D':
                printf("left\n");
                score = pressedLeft(board, score);
                break;
        }
        spawn(board);
        print_board(board, score);  
    }
        if (input == 'Q' || input == 'q') {
            printf("Quit\n");
            exit(0);
        }
    return score;
}

/* In main we are calling the functions and checking to 
make sure the user won. Also we are asking the user if they 
want to keep playing or not*/
int main (void){
    int i, j;
    int board[4][4] = {0};
    int score = 0;
    spawn(board);
    spawn(board);
    print_board(board, score);
    while(true) {
        score = arrows(board, score);

        
        if(highest_value_on_board(board) == 2048){
            played = true;
            getchar();
            printf("You win\n");
             printf("Do you want to play again. Y or N\n");
             char choice = getchar();
             if (choice == 'Y' || choice == 'y') {
                 board[4][4] = 0;
                
             } 
             else{
                 printf("Thanks for playing\n");
                 return 0;
             }
        }
        bool lost = true;
        for(i=0; i < 4; i++){
            for (j=0; j < 4; j++){
                if(board[i][j] == 0) {
                    lost = false; 
                 }
            }
        }
        if (lost == true){
        printf("You lose \n");
        printf("Do you want to play again. Y or N \n");
                char choice = getchar();
                if (choice == 'Y' || choice == 'y') {
                    board[4][4] = 0;
                } 
                else{
                    printf("Thanks for playing\n");
                    return 0;
                }
        }        
    }
    return 0; 
}
