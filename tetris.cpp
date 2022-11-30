#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    mIsDone = false;
}

void Game::handleInput() {
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
    }
}

void Game::update(char board[20][10], Block* fallingBlock) {
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
        if (event.type == sf::Event::EventType::KeyPressed){
            // LEFT ARROW PRESSED
            if (event.key.code == sf::Keyboard::Left){
                cout << "TSET" << endl;
                fallingBlock->movePos(board, -1, 0);
            }
            // RIGHT ARROW PRESSED
            else if (event.key.code == sf::Keyboard::Right) {
                fallingBlock->movePos(board, 1, 0);
            }
        }
    }
}

void Game::render(char board[20][10]) {
    sf::RectangleShape drawSquare;
    drawSquare.setSize(sf::Vector2f(40, 40));
    drawSquare.setFillColor(sf::Color::White);
    drawSquare.setOrigin(20, 20);

    // Basically it finds the center of the screen, then goes back half the size of the board from there
    // I know the multiplication could be simplified but it makes more sense when written this way
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(BLOCK_SIZE+BORDER_SIZE*2, BLOCK_SIZE+BORDER_SIZE*2));
    square.setTexture(&art);
    square.setOutlineThickness(0);

    sf::RectangleShape emptySquare;
    emptySquare.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    emptySquare.setOutlineColor(sf::Color(60,60,60));
    emptySquare.setOutlineThickness(BORDER_SIZE);

     for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i<20; i++)
                {
                    int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
                    int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;

                    switch(board[i][j]) {
                        case 'T':
                            square.setFillColor(sf::Color(160,0,240));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'O':
                            square.setFillColor(sf::Color(240,240,0));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'J':
                            square.setFillColor(sf::Color(0,0,240));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'L':
                            square.setFillColor(sf::Color(240,160,0));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'I':
                            square.setFillColor(sf::Color(0,240,240));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'Z':
                            square.setFillColor(sf::Color(240,0,0));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        case 'S':
                            square.setFillColor(sf::Color(0,240,0));
                            square.setPosition(posX, posY);
                            mWindow.draw(square);
                            break;
                        default: // Essentially the "else"
                            // This is only in the loop because it uses i
                            emptySquare.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i)));
                            emptySquare.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2, verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2);
                            mWindow.draw(emptySquare);
                    }
                }
            }
    mWindow.display();
    mWindow.clear(sf::Color(10, 10, 10));
}

bool Game::isDone() const {
    return (!mWindow.isOpen() || mIsDone);
}

void Game::loadTextures() {
    if(!art.loadFromFile("squar.png")) {
        cout << "no squar" << endl;
        exit(11);
    }
}

void initializeBoard(char board[20][10], char fillChar) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = fillChar;
        }
    }
}

void displayBoard(char board[20][10]) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

Block* getBlockType(int num) {
    Block *fallingBlock;
    switch(num) {
        case 1:
            fallingBlock = new T;
            break;
        case 2:
            fallingBlock = new O;
            break;
        case 3:
            fallingBlock = new J;
            break;
        case 4:
            fallingBlock = new L;
            break;
        case 5:
            fallingBlock = new I;
            break;
        case 6:
            fallingBlock = new Z;
            break;
        case 7:
            fallingBlock = new S;
            break;
        default:
            exit(2); // This shouldn't ever happen but just in case
            // fallingBlock = new T;
            // break;
    }
    return fallingBlock;
}

void spawnBlock(char board[20][10], Block* block) {
    vector<vector<char>> spriteSheet = block->getSprite();
    int start = block->getStartingRow();
    for(int i = 0; i < 5-start; i++) {
        for(int j = 0; j < 5; j++) {
            if(spriteSheet[i+start][j] != '-')
                board[i][2+j] = spriteSheet[i+start][j];
        }
    }
    block->posY = 2-start;
    block->posX = 4;
}

// friend void rotate() {
//     index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
// }

// friend char getChar() { return mChar; }

// friend int getStartingRow() { return startRow; }

// friend vector<vector<char>> getSprite() {
//     vector<vector<char>> spriteArray(5, vector<char>(5));
//     for(int i = 0; i < 5; i++) {
//         for(int j = 0; j < 5; j++) {
//         spriteArray[i][j] = shape[index][i][j];
//         }
//     }
//     return spriteArray;
// }

// friend void movePos(char board[20][10], int moveX, int moveY) {
//     for(int i = -2; i < 3; i++) {
//         for(int j = -2; j < 3; j++) {
//         if(shape[index][i+2][j+2] != '-') {
//             board[posY+i][posX+j] = '-';
//         }
//         }
//     }
//     cout << "movePos ran" << endl;
//     posX += moveX;
//     posY += moveY;
//     for(int i = -2; i < 3; i++) {
//         for(int j = -2; j < 3; j++) {
//         board[posY+i][posX+j] = shape[index][i+2][j+2];
//         }
//     }
// }