#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using std::cout;
using std::endl;
using std::vector;

class Block {

   public:
      int index = 0;
      int posX = 0, posY = 0;
      char mChar;
      // sf::Color color;
      // sf::Texture texture;
      vector<vector<vector<char>>> shape;

      virtual void rotate() = 0;
      virtual vector<vector<char>> getSprite() = 0;
      virtual char getChar() = 0;
      virtual int getStartingRow() = 0;
      virtual bool movePos(char board[20][10], int moveX, int moveY) = 0;

   private:

   
};

class T : public Block {
   int startRow = 1;
   char mChar = 'T';
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

   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }

   public:

      
};

class O : public Block {
   int startRow = 2;
   char mChar = 'O';
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

   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }

};

class J : public Block {
   int startRow = 1;
   char mChar = 'J';
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
   
   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }
};

class L : public Block {
   int startRow = 1;
   char mChar = 'L';
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

   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }
};

class I : public Block {
   int startRow = 2;
   char mChar = 'I';
   vector<vector<vector<char>>> shape={{{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','I','I','I','I'},
                                        {'-','2','2','2','2'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','-','2','-','-'}},

                                       {{'-','-','-','-','-'},
                                        {'-','-','-','-','-'},
                                        {'4','I','I','I','I'},
                                        {'-','2','2','2','2'},
                                        {'-','-','-','-','-'}},
 
                                       {{'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','4','I','6','-'},
                                        {'-','-','2','-','-'}}};
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
   
   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }
};

class Z : public Block {
   int startRow = 1;
   char mChar = 'Z';
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

   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }
};

class S : public Block {
   int startRow = 1;
   char mChar = 'S';
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
   void rotate() {
      index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
   }

   char getChar() { return mChar; }

   int getStartingRow() { return startRow; }

   vector<vector<char>> getSprite() {
      vector<vector<char>> spriteArray(5, vector<char>(5));
      for(int i = 0; i < 5; i++) {
         for(int j = 0; j < 5; j++) {
            if(posY < 2 || posX < 2) { continue; }
            spriteArray[i][j] = shape[index][i][j];
         }
      }
      return spriteArray;
   }

   bool movePos(char board[20][10], int moveX, int moveY) {
      // COLLISION CHECKING
      for(int i = -2; i <= 2; i++) {                     
         for(int j = -2; j <= 2; j++) {                  
            if(!canMove(board, moveX, moveY, i, j)) {    
               cout << "can't move" << endl;            
               return false;                             
            }                                            
         }                                               
      }                                                  
      
      // CLEARING CURRENT BLOCK FROM BOARD
      for(int i = -2; i <= 2; i++) {
         for(int j = -2; j <= 2; j++) {
            if(shape[index][i+2][j+2] == mChar) {
               if((posY + i < 0 || posX + i < 0)) { continue; }
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
            if((posY + i < 0 || posX + i < 0)) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION LEFT" << endl;
            return false;
         }
      }
      if(moveY > 0) { // MOVING DOWN
         if( (shape[index][i+2][j+2] == '1' || shape[index][i+2][j+2] == '2' || shape[index][i+2][j+2] == '3')  &&  board[posY+i][posX+j] != '-') {
            cout << "COLLISION DOWN" << endl;
            return false;
         }
      }
      return true;
   }

};

void initializeBoard(char board[20][10], char fillChar);
void displayBoard(char board[20][10]);
Block* getBlockType(int num);
void spawnBlock(char board[20][10], Block* block);

class Game
{
   
 public:
    Game();
    ~Game(){};
    void handleInput(char board[20][10], Block* fallingBlock);
    void loadTextures();
    void loadFont();
    void update(char board[20][10], Block* fallingBlock);
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
    void drawHighscore();
    void drawCurrentscore();
    sf::RectangleShape square;
    sf::RectangleShape boardSprite;
    sf::Texture art;
    sf::Texture back;
    sf::Font font;
    sf::Vector2i mIncrement;
   
};

#endif