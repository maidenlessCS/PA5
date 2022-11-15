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
    void loadTextures();
    void update(char board[20][10]);
    void render(char board[20][10]);
    bool isDone() const;
    int WINDOW_SIZE_X = 250;
    int WINDOW_SIZE_Y = 500;
    int BLOCK_SIZE = 20;
    int BORDER_SIZE = 2;
   //  int WINDOW_SIZE_X = 1024;
   //  int WINDOW_SIZE_Y = 812;
    int posX = 0;
 private:
    sf::RenderWindow mWindow;
    bool mIsDone;
    sf::RectangleShape square;
    sf::RectangleShape boardSprite;
    sf::Texture art;
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
   //char shape[5][5];

};

class Cross : Block {
   char shape[2][3] = {{'_','X','_'},
                       {'X','X','X'}};
};

class Square : Block {
   char shape[2][2] = {{'X','X'},
                       {'X','X'}};
};

class LLeft : Block {
   char shape[2][3] = {{'X','X','X'},
                       {'_','_','X'}};
};

class LRight : Block {
   char shape[2][3] = {{'X','X','X'},
                       {'X','_','_'}};
};

class Line : Block {
   char shape[1][4] = {{'X','X','X','X'}};
};

void initializeBoard(char board[20][10], char fillChar);
void displayBoard(char board[20][10]);

#endif