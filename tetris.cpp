#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    //square.setSize(sf::Vector2f(400, 800));
    square.setOrigin(62.f / 2.f, 62.f / 2.f);
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

void Game::update(char board[20][10]) {
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

void Game::render(char board[20][10]) {
    mWindow.clear(sf::Color::Black);
     for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i<20; i++)
                {
                    if (board[i][j] == '-')
                    {
                        sf::RectangleShape square;
                        square.setSize(sf::Vector2f(20, 20));
                        square.setFillColor(sf::Color(255,255,255));
                        square.setPosition(20*j+5*j,20*i+5*i);
                        mWindow.draw(square);
                    }
                }
            }
    //mWindow.draw(square);
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