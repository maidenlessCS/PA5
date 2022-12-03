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
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock

    float secondsCounter = 0;

    while(!game.isDone())
    {
        sf::Time elapsedTime = clock.restart();
        secondsCounter += elapsedTime.asSeconds();
        game.handleInput(board, fallingBlock);
        game.update(board, fallingBlock);
        if(secondsCounter >= 1) {
            if(!fallingBlock->movePos(board, 0, 1)) {
                fallingBlock = nullptr;
                game.explosion(board);
                // this runs when it is unable to move downwards, so itll
                // be where we create and assign a new falling block
                cout << "move failed" << endl;
                game.placementPoints();
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

    return 0;

}