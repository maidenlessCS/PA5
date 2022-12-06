#include "tetris.h"

int main() {
    srand (time(NULL));

    Game game;
    game.loadTextures();
    game.loadFont();
    //Main menu prototype
    bool gameStart = false;
    bool overPlayButton = false;
    bool overExitButton = false;
    while(!gameStart)
    {
        game.mainMenuBackground();
        game.mainMenuButtons(gameStart, overPlayButton, overExitButton);
        
    }

    game.getHighscore();

    char board[20][10];

    initializeBoard(board, '-');

    char nextBoard[5][5];

    int randBlock = rand() % 7 + 1;
    Block *fallingBlock;
    setBlockType(randBlock, fallingBlock);

    randBlock = rand() % 7 + 1;
    Block *nextBlock;
    setBlockType(randBlock, nextBlock);

    spawnBlock(board, fallingBlock);

    displayBoard(board);
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock

    float secondsCounter = 0;

    bool newBlock = false;

    while(!game.isDone())
    {
        sf::Time elapsedTime = clock.restart();
        secondsCounter += elapsedTime.asSeconds();
        newBlock = game.handleInput(board, fallingBlock);
        cout << "speed mult: " << game.SPEED_MULT << endl;
        if(secondsCounter >= game.SPEED_MULT) {
            if(!fallingBlock->movePos(board, 0, 1) || newBlock) {
                newBlock = false;
                game.explosion(board);
                game.placementPoints();

                // Spawning new block
                int randBlock = rand() % 7 + 1;
                fallingBlock = nextBlock;
                setBlockType(randBlock, nextBlock);
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

    delete fallingBlock;
    delete nextBlock;

    return 0;

}