#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath> // for round()
using std::cout;
using std::endl;
using std::vector;

class Block {

   public:
      int index = 0;
      int posX = 0, posY = 0;
      char mChar;
      float centerX, centerY;
      // sf::Color color;
      // sf::Texture texture;
      vector<vector<vector<char>>> shape;

      virtual void rotate(char board[20][10]) = 0;
      virtual vector<vector<char>> getSprite() = 0;
      virtual char getChar() = 0;
      virtual float getCenterX() = 0;
      virtual float getCenterY() = 0;
      virtual int getStartingRow() = 0;
      virtual bool movePos(char board[20][10], int moveX, int moveY) = 0;

   private:

   
};

class T : public Block {
   int startRow = 1;
   char mChar = 'T';
   float centerX = 2.5;
   float centerY = 2;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','4','T','6','-'},
                                        {'4','T','T','T','6'},
                                        {'-','2','2','2','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','4','T','6','-'},
                                        {'-','4','T','T','6'},
                                        {'-','4','T','3','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','T','T','T','6'},
                                        {'-','1','T','3','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','4','T','6','-'},
                                        {'4','T','T','6','-'},
                                        {'-','1','T','6','-'},
                                        {'-','-','2','-','-'}}};

      void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);

   public:

      
};

class O : public Block {
   int startRow = 2;
   char mChar = 'O';
   float centerX = 3;
   float centerY = 3;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','4','O','O','6'},
                                        {'-','4','O','O','6'},
                                        {'-','-','2','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','4','O','O','6'},
                                        {'-','4','O','O','6'},
                                        {'-','-','2','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','4','O','O','6'},
                                        {'-','4','O','O','6'},
                                        {'-','-','2','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','4','O','O','6'},
                                        {'-','4','O','O','6'},
                                        {'-','-','2','2','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);
};

class J : public Block {
   int startRow = 1;
   char mChar = 'J';
   float centerX = 2.5;
   float centerY = 2;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'4','J','6','-','-'},
                                        {'4','J','J','J','6'},
                                        {'-','2','2','2','-'},
                                        {'-','-','-','-','-'}},
                                        
                                       {{'-','-','-','-','-'},
                                        {'-','4','J','J','6'},
                                        {'-','4','J','3','-'},
                                        {'-','4','J','6','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','J','J','J','6'},
                                        {'-','2','1','J','6'},
                                        {'-','-','-','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','4','J','6','-'},
                                        {'-','4','J','6','-'},
                                        {'4','J','J','6','-'},
                                        {'-','2','2','-','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);
};

class L : public Block {
   int startRow = 1;
   char mChar = 'L';
   float centerX = 2.5;
   float centerY = 2;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','4','L','6'},
                                        {'4','L','L','L','6'},
                                        {'-','2','2','2','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','4','L','6','-'},
                                        {'-','4','L','6','-'},
                                        {'-','4','L','L','6'},
                                        {'-','-','2','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','L','L','L','6'},
                                        {'4','L','3','2','-'},
                                        {'-','2','-','-','-'}},
                                        
                                       {{'-','-','-','-','-'},
                                        {'4','L','L','6','-'},
                                        {'-','1','L','6','-'},
                                        {'-','4','L','6','-'},
                                        {'-','-','2','-','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);
};

class I : public Block {
   int startRow = 1;
   char mChar = 'I';
   float centerX = 3;
   float centerY = 1.5;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'4','I','I','I','I'},
                                        {'-','2','2','2','2'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'4','I','I','I','I'},
                                        {'-','2','2','2','2'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','-','2','-','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);
};

class Z : public Block {
   int startRow = 1;
   char mChar = 'Z';
   float centerX = 2.5;
   float centerY = 2;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'4','Z','Z','6','-'},
                                        {'-','1','Z','Z','6'},
                                        {'-','-','2','2','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','4','Z','6'},
                                        {'-','4','Z','Z','6'},
                                        {'-','4','Z','3','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','Z','Z','6','-'},
                                        {'-','1','Z','Z','6'},
                                        {'-','-','2','2','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','4','Z','6','-'},
                                        {'4','Z','Z','6','-'},
                                        {'4','Z','3','-','-'},
                                        {'-','2','-','-','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);
};

class S : public Block {
   int startRow = 1;
   char mChar = 'S';
   float centerX = 2.5;
   float centerY = 2;
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','4','S','S','6'},
                                        {'4','S','S','3','-'},
                                        {'-','2','2','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'-','4','S','6','-'},
                                        {'-','4','S','S','6'},
                                        {'-','-','1','S','6'},
                                        {'-','-','-','2','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','4','S','S','6'},
                                        {'4','S','S','3','-'},
                                        {'-','2','2','-','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'4','S','6','-','-'},
                                        {'4','S','S','6','-'},
                                        {'-','1','S','6','-'},
                                        {'-','-','2','-','-'}}};
   void rotate(char board[20][10]);
      vector<vector<char>> getSprite();
      char getChar();
      float getCenterX();
      float getCenterY();
      int getStartingRow();
      bool movePos(char board[20][10], int moveX, int moveY);
      bool canMove(char board[20][10], int moveX, int moveY, int i, int j);

};

void initializeBoard(char board[20][10], char fillChar);
void displayBoard(char board[20][10]);
void setBlockType(int num, Block* &fallingBlock);
void spawnBlock(char board[20][10], Block* block);

class Game
{
   
 public:
    Game();
    ~Game(){};
    bool handleInput(char board[20][10], Block* fallingBlock);
    void loadTextures();
    void loadFont();
    void render(char board[20][10], Block* nextBlock);
    void explosion(char board[20][10]);
    void placementPoints();
    bool isDone() const;
    void gameEnd(char board[20][10], Block* fallingBlock);
    void getHighscore();
    void checkScores();
    int WINDOW_SIZE_X = 650;
    int WINDOW_SIZE_Y = 600;
    // Each block is sized to BLOCK_SIZE + (BORDER_SIZE * 2)
    int BLOCK_SIZE = 22;
    int BORDER_SIZE = 1;
    float SPEED_MULT = 1;
    // This is purely here to temporariyl save speed
    // when decreasing it for holding down arrow.
    // I could've passed a float instead of using a public
    // but this was simpler so I just did it this way.
    float TEMP_SPEED = 1;
    int posX = 0;
   sf::RenderWindow mWindow;
   sf::Font font;
   sf::Texture art;
   sf::Texture back;
 private:
    bool mIsDone;
    void drawHighscore();
    void drawCurrentscore();
    void squareColor(char current, sf::RectangleShape &square);
    std::string scoreToString(int score);
    sf::RectangleShape square;
    sf::RectangleShape boardSprite;
    
    sf::Vector2i mIncrement;
    float currentScore = 0;
    int highestScore =0;
   
};

#endif