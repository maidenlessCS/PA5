#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    boardSprite.setSize(sf::Vector2f(400, 800));
    boardSprite.setOrigin(200, 400);
    boardSprite.setPosition(sf::Vector2f(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2));
    boardSprite.setOutlineColor(sf::Color(0, 97, 255));
    boardSprite.setOutlineThickness(6);
    boardSprite.setFillColor(sf::Color(0, 10, 51));
    mIncrement = sf::Vector2i(4, 4);
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

void Game::update() {
    sf::Event event;
        while(mWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                // Close window button clicked.
                mWindow.close();
            }
            if (event.type == sf::Event::EventType::KeyPressed){

                if (event.key.code == sf::Keyboard::Left){
                    // Do something here
                    if(posX > 0+5) {
                        posX-=5;
                    }
                    square.setPosition(sf::Vector2f(posX, square.getPosition().y));
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    if(posX < WINDOW_SIZE_X-square.getSize().x - 5) {
                        posX+=5;
                    }
                    square.setPosition(sf::Vector2f(posX, square.getPosition().y));
                    // Do something here
                }
                
            }
        }
}

void Game::moveCherry() {
    sf::Vector2u winSize = mWindow.getSize();
    int cherryX = 62;
    int cherryY = 62;
    if ((square.getPosition().x + (cherryX / 2) > winSize.x && mIncrement.x > 0) ||
        (square.getPosition().x - (cherryX / 2) < 0 && mIncrement.x < 0))
    {
        // Reverse the direction on X axis
        mIncrement.x = -mIncrement.x;
    }
    if ((square.getPosition().y + (cherryY / 2) > winSize.y && mIncrement.y > 0) ||
        (square.getPosition().y - (cherryY / 2) < 0 && mIncrement.y < 0))
    {
        // Reverse the direction on Y axis.
        mIncrement.y = -mIncrement.y;
    }
    square.setPosition(
        square.getPosition().x + mIncrement.x,
        square.getPosition().y + mIncrement.y);
}

void Game::render() {
    mWindow.clear(sf::Color(91, 149, 245));



    sf::RectangleShape drawSquare;
    drawSquare.setSize(sf::Vector2f(40, 40));
    drawSquare.setFillColor(sf::Color::White);
    drawSquare.setOrigin(20, 20);
    // for(int i = 0; i < 20; i++) {
    //     for(int j = 0; j < 10; j++) {
    //         cout << board[i][j] << ' ';
    //     }
    // }




    mWindow.draw(boardSprite);
    mWindow.display();
}

bool Game::isDone() const {
    return (!mWindow.isOpen() || mIsDone);
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