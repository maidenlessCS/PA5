#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using std::cout;
using std::endl;

class Game
{
   
 public:
    Game();
    ~Game(){};
    void handleInput();
    void update(char board[20][10]);
    void render(char board[20][10]);
    bool isDone() const;
    int WINDOW_SIZE_X = 250;
    int WINDOW_SIZE_Y = 500;
    int posX = 0;
 private:
    sf::RenderWindow mWindow;
    bool mIsDone;
    sf::RectangleShape square;
    sf::Vector2i mIncrement;
    void moveCherry();
   
};

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