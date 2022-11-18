#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
using std::cout;
using std::endl;
using std::vector;

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
    int WINDOW_SIZE_X = 700;
    int WINDOW_SIZE_Y = 650;
    // Each block is sized to BLOCK_SIZE + (BORDER_SIZE * 2)
    int BLOCK_SIZE = 28;
    int BORDER_SIZE = 1;
    int posX = 0;
 private:
    sf::RenderWindow mWindow;
    bool mIsDone;
    sf::RectangleShape square;
    sf::RectangleShape boardSprite;
    sf::Texture art;
    sf::Vector2i mIncrement;
   
};

class Block {

   public:
      int index = 0;
      char mChar;
      // sf::Color color;
      // sf::Texture texture;
      vector<vector<vector<char>>> shape;

      virtual void rotate() = 0;
      virtual vector<vector<char>> getSprite() = 0;
      virtual char getChar() = 0;
      virtual int getStartingRow() = 0;

   private:

   
};

class T : public Block {
   int startRow = 1;
   char mChar = 'T';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','T','-','-'},
                                        {'-','T','T','T','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','T','-','-'},
                                        {'-','-','T','T','-'},
                                        {'-','-','T','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','T','T','T','-'},
                                        {'-','-','T','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','T','-','-'},
                                        {'-','T','T','-','-'},
                                        {'-','-','T','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }

   public:

      
};

class O : public Block {
   int startRow = 2;
   char mChar = 'O';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','O','O','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

class J : public Block {
   int startRow = 1;
   char mChar = 'J';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','J','-','-','-'},
                                        {'-','J','J','J','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},
                                        
                                       {{'-','-','-','-','-'},
                                        {'-','-','J','J','-'},
                                        {'-','-','J','-','-'},
                                        {'-','-','J','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','J','J','J','-'},
                                        {'-','-','-','J','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','J','-','-'},
                                        {'-','-','J','-','-'},
                                        {'-','J','J','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

class L : public Block {
   int startRow = 1;
   char mChar = 'L';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','-','L','-'},
                                        {'-','L','L','L','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','L','-','-'},
                                        {'-','-','L','-','-'},
                                        {'-','-','L','L','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','L','L','L','-'},
                                        {'-','L','-','-','-'},
                                        {'-','-','-','-','-'}},
                                        
                                       {{'-','-','-','-','-'},
                                        {'-','L','L','-','-'},
                                        {'-','-','L','-','-'},
                                        {'-','-','L','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

class I : public Block {
   int startRow = 2;
   char mChar = 'I';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','I','I','I','I'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','I','I','I','I'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','I','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

class Z : public Block {
   int startRow = 1;
   char mChar = 'Z';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','Z','Z','-','-'},
                                        {'-','-','Z','Z','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','Z','-'},
                                        {'-','-','Z','Z','-'},
                                        {'-','-','Z','-','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','Z','Z','-','-'},
                                        {'-','-','Z','Z','-'},
                                        {'-','-','-','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','Z','-','-'},
                                        {'-','Z','Z','-','-'},
                                        {'-','Z','-','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

class S : public Block {
   int startRow = 1;
   char mChar = 'S';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','S','S','-'},
                                        {'-','S','S','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'-','-','S','-','-'},
                                        {'-','-','S','S','-'},
                                        {'-','-','-','S','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'-','-','S','S','-'},
                                        {'-','S','S','-','-'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','-','-','-','-'},
                                        {'-','S','-','-','-'},
                                        {'-','S','S','-','-'},
                                        {'-','-','S','-','-'},
                                        {'-','-','-','-','-'}}};
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }
};

void initializeBoard(char board[20][10], char fillChar);
void displayBoard(char board[20][10]);
Block* getBlockType(int num);
void spawnBlock(char board[20][10], Block* block);

#endif