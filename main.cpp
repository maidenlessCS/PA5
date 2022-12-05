#include "tetris.h"

int main() {
    srand (time(NULL));

    char board[20][10];

    initializeBoard(board, '-');

    char nextBoard[5][5];

    int randBlock = rand() % 7 + 1;
    Block *fallingBlock = getBlockType(5);
    randBlock = rand() % 7 + 1;
    Block *nextBlock = getBlockType(randBlock);

    board[19][0] = 'J';
    board[19][1] = 'J';
    board[19][2] = 'J';
    board[19][3] = 'J';
    board[19][4] = 'J';
    board[19][5] = 'J';
    board[19][6] = 'J';
    board[19][7] = 'J';
    board[19][8] = 'J';
    board[18][0] = 'J';
    board[18][1] = 'J';
    board[18][2] = 'J';
    board[18][3] = 'J';
    board[18][4] = 'J';
    board[18][5] = 'J';
    board[18][6] = 'J';
    board[18][7] = 'J';
    board[18][8] = 'J';

    // cout << fallingBlock->index << endl;
    // fallingBlock->rotate(board);
    // cout << fallingBlock->index << endl;

    //fallingBlock->rotate();
    // fallingBlock->rotate(); // this is just for resetting the rotation, or rotating back around
    // fallingBlock->rotate();

    // This is temporary, just to test and show how this will work
    // by getting the sprites of each block. It gets it at the index of its rotation
    // so by using rotate() first it will change which array it returns

    spawnBlock(board, fallingBlock);

    displayBoard(board);

    Game game;
    game.loadTextures();
    game.loadFont();
    //Main menu prototype
    bool gameStart = false;
    bool overPlayButton = false;
    while(!gameStart)
    {
        sf::RectangleShape menuBackground;
        menuBackground.setSize(sf::Vector2f(700, 650));
        menuBackground.setTexture(&game.back);
        game.mWindow.draw(menuBackground);
        sf::RectangleShape playButton;
        playButton.setSize(sf::Vector2f(100,50));
        playButton.setOrigin(50,25);
        playButton.setPosition(sf::Vector2f(350,325));
        playButton.setOutlineThickness(5);
        sf::Text play;
        if (overPlayButton){
            playButton.setFillColor(sf::Color(152,181,227, 190));
            play.setFillColor(sf::Color(255,255,255,190));
            playButton.setOutlineColor(sf::Color(255,255,255,190));
        }
        else{
            playButton.setFillColor(sf::Color(34,59,140, 190));  
            play.setFillColor(sf::Color(0,0,0,190));
            playButton.setOutlineColor(sf::Color(0,0,0,190));
        }
        game.mWindow.draw(playButton);
        play.setCharacterSize(35);
        play.setFont(game.font);
        play.setString("Play");
        sf::FloatRect textRect = play.getLocalBounds();
        play.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
        play.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y));
        game.mWindow.draw(play);
        sf::Event event;
        while(game.mWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                game.mWindow.close();
                exit(0);
            }
            sf::Vector2i mousePosition = sf::Mouse::getPosition(game.mWindow);
            bool mouseInButton =    mousePosition.x >= playButton.getPosition().x - playButton.getSize().x/2
                                    && mousePosition.x <= playButton.getPosition().x + playButton.getSize().x/2
                                    && mousePosition.y >= playButton.getPosition().y - playButton.getSize().y/2
                                    && mousePosition.y <= playButton.getPosition().y + playButton.getSize().y/2;
        if(event.type == sf::Event::MouseMoved)
            {
                if(mouseInButton)
                {
                    overPlayButton = true;
                }
                else{
                    overPlayButton = false;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(mouseInButton){
                        gameStart = true;
                        }
                    }
                }
        }
        game.mWindow.display();
        game.mWindow.clear(sf::Color(10, 10, 10));
    }

    game.getHighscore();
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock

    float secondsCounter = 0;

    bool newBlock = false;

    while(!game.isDone())
    {
        sf::Time elapsedTime = clock.restart();
        secondsCounter += elapsedTime.asSeconds();
        newBlock = game.handleInput(board, fallingBlock);
        game.update(board, fallingBlock);
        cout << "speed mult: " << game.SPEED_MULT << endl;
        if(secondsCounter >= game.SPEED_MULT) {
            if(!fallingBlock->movePos(board, 0, 1) || newBlock) {
                newBlock = false;
                fallingBlock = nullptr;
                game.explosion(board);
                game.placementPoints();

                // Spawning new block
                int randBlock = rand() % 7 + 1;
                fallingBlock = nextBlock;
                nextBlock = getBlockType(randBlock);
                spawnBlock(board, fallingBlock);
            }
            secondsCounter = 0;
        }
        game.render(board, nextBlock);

        displayBoard(board);
        sf::sleep(elapsedTime + TIME_PER_FRAME - clock.getElapsedTime());
        game.gameEnd(board, fallingBlock);
    }
    game.checkScores();

    return 0;

}