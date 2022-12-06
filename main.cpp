#include "tetris.h"

int main() {
    srand (time(NULL));

    char board[20][10];

    initializeBoard(board, '-');

    char nextBoard[5][5];

    int randBlock = rand() % 7 + 1;
    Block *fallingBlock = getBlockType(1);
    randBlock = rand() % 7 + 1;
    Block *nextBlock = getBlockType(randBlock);

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
    bool overExitButton = false;
    while(!gameStart)
    {
        //draws main menu background
        sf::RectangleShape menuBackground;
        menuBackground.setSize(sf::Vector2f(700, 650));
        menuBackground.setTexture(&game.back2);
        game.mWindow.draw(menuBackground);
        
        sf::RectangleShape blackground;
        blackground.setSize(sf::Vector2f(700, 650));
        blackground.setFillColor(sf::Color(0,0,0,160));
        game.mWindow.draw(blackground);

        sf::RectangleShape playButton;
        playButton.setSize(sf::Vector2f(150,75));
        playButton.setOrigin(playButton.getSize().x/2, playButton.getSize().y/2);
        playButton.setPosition(sf::Vector2f(game.WINDOW_SIZE_X - game.WINDOW_SIZE_X/2,game.WINDOW_SIZE_Y - game.WINDOW_SIZE_Y/2));
        playButton.setOutlineThickness(5);

        sf::RectangleShape exitButton;
        exitButton.setSize(sf::Vector2f(150,75));
        exitButton.setOrigin(exitButton.getSize().x/2, exitButton.getSize().y/2);
        exitButton.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y+game.WINDOW_SIZE_Y/6));
        exitButton.setOutlineThickness(5);

        sf::RectangleShape title;
        title.setSize(sf::Vector2f(984/1.75, 168/1.75));
        title.setTexture(&game.title);
        title.setOrigin(title.getSize().x/2, title.getSize().y/2);
        title.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y-game.WINDOW_SIZE_Y/6));
        game.mWindow.draw(title);

        sf::Text play;
        sf::Text exit;
        
        playButton.setFillColor(sf::Color(34,59,140, 230));  
        play.setFillColor(sf::Color(0,0,0,230));
        playButton.setOutlineColor(sf::Color(0,0,0,230));

        exitButton.setFillColor(sf::Color(223,18,18, 230));  
        exit.setFillColor(sf::Color(0,0,0,230));
        exitButton.setOutlineColor(sf::Color(0,0,0,230));

        
        play.setCharacterSize(35);
        play.setFont(game.font);
        play.setString("Play");
        sf::FloatRect textRect = play.getLocalBounds();
        play.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
        play.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y));
        

        exit = play;
        
        exit.setString("Exit");
        exit.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y+game.WINDOW_SIZE_Y/6));

        if (overPlayButton){
            playButton.setFillColor(sf::Color(152,181,227, 230));
            play.setFillColor(sf::Color(255,255,255,230));
            playButton.setOutlineColor(sf::Color(255,255,255,230));
        }
        else if (overExitButton){
            exitButton.setFillColor(sf::Color(255,65,65, 230));
            exit.setFillColor(sf::Color(255,255,255,230));
            exitButton.setOutlineColor(sf::Color(255,255,255,230));
        }

        game.mWindow.draw(playButton);
        game.mWindow.draw(exitButton);
        game.mWindow.draw(play);
        game.mWindow.draw(exit);

        sf::Event event;
        while(game.mWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                game.mWindow.close();
                std::exit(0);
            }
            sf::Vector2i mousePosition = sf::Mouse::getPosition(game.mWindow);
            bool mouseInPlayButton =    mousePosition.x >= playButton.getPosition().x - playButton.getSize().x/2
                                    && mousePosition.x <= playButton.getPosition().x + playButton.getSize().x/2
                                    && mousePosition.y >= playButton.getPosition().y - playButton.getSize().y/2
                                    && mousePosition.y <= playButton.getPosition().y + playButton.getSize().y/2;
            bool mouseInExitButton =    mousePosition.x >= exitButton.getPosition().x - exitButton.getSize().x/2
                                    && mousePosition.x <= exitButton.getPosition().x + exitButton.getSize().x/2
                                    && mousePosition.y >= exitButton.getPosition().y - exitButton.getSize().y/2
                                    && mousePosition.y <= exitButton.getPosition().y + exitButton.getSize().y/2;
        if(event.type == sf::Event::MouseMoved)
            {
                overPlayButton = mouseInPlayButton;
                overExitButton = mouseInExitButton;
            }
            if (event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button==sf::Mouse::Left){
                        if(mouseInPlayButton){
                            gameStart = true;
                        }
                        if(mouseInExitButton){
                            game.mWindow.close();
                            std::exit(0);
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