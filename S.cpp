#include "tetris.h"

void S::rotate(char board[20][10]) {
      // CLEARING CURRENT BLOCK FROM BOARD
    for(int i = -2; i <= 2; i++) {
        for(int j = -2; j <= 2; j++) {
        if(shape[index][i+2][j+2] == mChar) {
            if(posY + i < 0 ) { continue; }
            board[posY+i][posX+j] = '-';
        }
        }
    }

    int startIndex = index;
    bool canRotate;

    do {
        canRotate = true;
        
        // ROTATING INDEX OF BLOCK
        index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
        // COLLISION CHECKING
        for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {                  
                if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                    canRotate = false;
                    break;
                }
            }                                               
        }
    } while (!canRotate && index != startIndex);

    // RE-ADDING THE BLOCK TO THE BOARD WITH INDEX (EITHER UPDATED OR NOT DEPENDING ON WHILE LOOP)
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
        if(posY + i < 0 ) { continue; }
        if(shape[index][i+2][j+2] == mChar)
            board[posY+i][posX+j] = shape[index][i+2][j+2];
        }
    }
}

char S::getChar() { return mChar; }

float S::getCenterX() { return centerX; }
float S::getCenterY() { return centerY; }

int S::getStartingRow() { return startRow; }

vector<vector<char>> S::getSprite() {
    vector<vector<char>> spriteArray(5, vector<char>(5));
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
        spriteArray[i][j] = shape[index][i][j];
        }
    }
    return spriteArray;
}

bool S::movePos(char board[20][10], int moveX, int moveY) {
    // COLLISION CHECKING
    for(int i = -2; i <= 2; i++) {                     
        for(int j = -2; j <= 2; j++) {                  
        if(!canMove(board, moveX, moveY, i, j)) {    
            return false;                             
        }                                            
        }                                               
    }                                                  
    
    // CLEARING CURRENT BLOCK FROM BOARD
    for(int i = -2; i <= 2; i++) {
        for(int j = -2; j <= 2; j++) {
        if(shape[index][i+2][j+2] == mChar) {
            if(posY + i < 0) { continue; }
            board[posY+i][posX+j] = '-';
        }
        }
    }
    
    // UPDATING BLOCK'S INTERNAL POSITION
    posX += moveX;
    posY += moveY;

    // RE-ADDING THE BLOCK TO THE BOARD IN THE NEW POSITION
    for(int i = -2; i < 3; i++) {
        for(int j = -2; j < 3; j++) {
        if(posY + i < 0) { continue; }
        if(shape[index][i+2][j+2] == mChar)
            board[posY+i][posX+j] = shape[index][i+2][j+2];
        }
    }
    return true;
}

bool S::canMove(char board[20][10], int moveX, int moveY, int i, int j) {
    if(moveX > 0) { // MOVING RIGHT
        if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
        return false;
        }
    }
    else if (moveX < 0) { // MOVING LEFT
        if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j <=-1 || board[posY+i][posX+j] != '-')) {
        return false;
        }
    }
    if(moveY > 0) { // MOVING DOWN
        if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
        return false;
        }
    }
    return true;
}