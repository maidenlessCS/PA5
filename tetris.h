#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
using std::cout;
using std::endl;


class Block {

 public:
    virtual void rotate() = 0; // I'm not sure about this, if it's better than just not having
                               // function here at all and just having the child functions
                               // have them anyways (not virtual)
    char getChar();


 private:
    char mChar;


};

class Cross : Block {

};

class Square : Block {

};

class LLeft : Block {

};

class LRight : Block {

};

class Line : Block {

};

void initializeBoard(char board[20][10], char fillChar);
void displayBoard(char board[20][10]);

#endif