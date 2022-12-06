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
        game.mainMenuBackground();
        game.mainMenuButtons(gameStart, overPlayButton, overExitButton);
        
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