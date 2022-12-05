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
   void rotate(char board[20][10]) {
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
               if(shape[index][i+2][j+2] == mChar && board[posY+i][posX+j] != '-') {
                  canRotate = false;
                  break;
               }
            }                                               
         }
         cout << !canRotate << " " << (index != startIndex) << endl;

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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j <=-1 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING
         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING
         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING
         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING

         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if((index == 0 || index == 2) && posX >= 7) { // manual checking for I block since
            return false;                              // block is too big for array to have
         }                                             // right side detection
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING
         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
   void rotate(char board[20][10]) {
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

      // By doing a while loop, making a rotation attempt will continue to rotate
      // until a valid rotation is found, meaning it can skip over a rotation if it is invalid
      do {
         canRotate = true;

         // ROTATING INDEX OF BLOCK
         index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
         // COLLISION CHECKING
         for(int i = -2; i <= 2; i++) {                     
            for(int j = -2; j <= 2; j++) {
               if((shape[index][i+2][j+2] == mChar) && (posX+j >= 10 || posX+j < 0 || board[posY+i][posX+j] != '-')) {
                  cout << "canot rotat" << endl;
                  canRotate = false;
                  break;
               }
               else if(shape[index][i+2][j+2] == mChar) {
                  cout << posX + j << endl;
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

   char getChar() { return mChar; }

   float getCenterX() { return centerX; }
   float getCenterY() { return centerY; }

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
               if(posY + i < 0 ) { continue; }
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
            if(posY + i < 0 ) { continue; }
            if(shape[index][i+2][j+2] == mChar)
               board[posY+i][posX+j] = shape[index][i+2][j+2];
         }
      }
      return true;
   }

   bool canMove(char board[20][10], int moveX, int moveY, int i, int j) {
      if(moveX > 0) { // MOVING RIGHT
         if( (shape[index][i+2][j+2] == '6' || shape[index][i+2][j+2] == '3')  &&  (posX+j >= 10 || board[posY+i][posX+j] != '-')) {
            cout << "COLLISION RIGHT" << endl;
            return false;
         }
      }
      else if (moveX < 0) { // MOVING LEFT
         if( (shape[index][i+2][j+2] == '4' || shape[index][i+2][j+2] == '1')  &&  (posX+j < 0 || board[posY+i][posX+j] != '-')) {
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
    bool handleInput(char board[20][10], Block* fallingBlock);
    void loadTextures();
    void loadFont();
    void update(char board[20][10], Block* fallingBlock);
    void render(char board[20][10], Block* nextBlock);
    void explosion(char board[20][10]);
    void placementPoints();
    bool isDone() const;
    void gameEnd(char board[20][10], Block* fallingBlock);
    void getHighscore();
    void checkScores();
    int WINDOW_SIZE_X = 700;
    int WINDOW_SIZE_Y = 650;
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