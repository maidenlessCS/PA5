#include "tetris.h"

void initializeBoard(char board[20][10], char fillChar) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            //fills board it entered character, currently set to run as board's empty square
            board[i][j] = fillChar;
        }
    }
}

void displayBoard(char board[20][10]) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            //outputs board to terminal
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void setBlockType(int num, Block* &block) {
    //sets to a block type based on the number passed
    switch(num) {
        case 1:
            block = new T;
            break;
        case 2:
            block = new O;
            break;
        case 3:
            block = new J;
            break;
        case 4:
            block = new L;
            break;
        case 5:
            block = new I;
            break;
        case 6:
            block = new Z;
            break;
        case 7:
            block = new S;
            break;
        default:
            exit(2); // This shouldn't ever happen but just in case
            // fallingBlock = new T;
            // break;
    }
}

void spawnBlock(char board[20][10], Block* block) {
    //gets Block's shape
    vector<vector<char>> spriteSheet = block->getSprite();
    char blockChar = block->getChar();
    int start = block->getStartingRow();
    //puts the block into the game array
    for(int i = 0; i < 5-start; i++) {
        for(int j = 0; j < 5; j++) {
            if(spriteSheet[i+start][j] == blockChar)
                board[i][2+j] = spriteSheet[i+start][j];
        }
    }
    block->posY = 2-start;
    block->posX = 4;
}