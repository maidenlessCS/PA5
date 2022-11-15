#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    boardSprite.setSize(sf::Vector2f(400, 800));
    boardSprite.setOrigin(200, 400);
    boardSprite.setPosition(sf::Vector2f(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2));
    boardSprite.setOutlineColor(sf::Color(0, 97, 255));
    boardSprite.setOutlineThickness(6);
    boardSprite.setFillColor(sf::Color(0, 10, 51));
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
    //mWindow.clear(sf::Color::Black);
    //mWindow.clear(sf::Color(10, 10, 10));

    sf::RectangleShape drawSquare;
    drawSquare.setSize(sf::Vector2f(40, 40));
    drawSquare.setFillColor(sf::Color::White);
    drawSquare.setOrigin(20, 20);

    // Basically it finds the center of the screen, then goes back half the size of the board from there
    // I know the multiplication could be simplified but it makes more sense when written this way
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

    sf::RectangleShape square;

     for (int j = 0; j < 10; j++)
            {
                for (int i = 0; i<20; i++)
                {
                    if (board[i][j] == '-')
                    {
                        square.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                        square.setTexture(NULL); // Clears texture
                        square.setOutlineColor(sf::Color(60,60,60));
                        square.setOutlineThickness(BORDER_SIZE);
                        // Color starts at 40 because 2*20 gets to 40 so 40-(2*i) becomes 0 by the end of the loop
                        // Doing it this way allows the gradient to start grey and end black
                        square.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i)));
                        square.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2, verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2);
                        mWindow.draw(square);
                    }
                    else if (board[i][j] == 'l')
                    {
                        square.setSize(sf::Vector2f(BLOCK_SIZE+BORDER_SIZE*2, BLOCK_SIZE+BORDER_SIZE*2));
                        square.setTexture(&art);
                        square.setOutlineThickness(0);
                        square.setFillColor(sf::Color(200,0,255));
                        // im writing this comment down for later for cleaning up code so i dont forget why its done this way
                        // the offset is to center it, it's explained above the loops
                        // the subtracting of broder size is purely for colored blocks and its to correct a single pixel
                        // missalignment that would otherwise be there
                        square.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE, verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE);
                        mWindow.draw(square);
                    }
                    else if (board[i][j] == 's')
                    {
                        square.setSize(sf::Vector2f(BLOCK_SIZE+BORDER_SIZE*2, BLOCK_SIZE+BORDER_SIZE*2));
                        square.setTexture(&art);
                        square.setFillColor(sf::Color(60,255,30));
                        square.setOutlineThickness(0);
                        square.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE, verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE);
                        mWindow.draw(square);
                    }
                }
            }
    mWindow.display();
    mWindow.clear(sf::Color(10, 10, 10));
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

void Game::loadTextures() {
    if(!art.loadFromFile("squar.png")) {
        cout << "no squar" << endl;
        exit(11);
    }
}