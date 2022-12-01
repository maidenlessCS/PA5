#include "tetris.h"

int main() {

    srand (time(NULL));

    char board[20][10];

    initializeBoard(board, '-');

    int randBlock = rand() % 7 + 1;
    Block *fallingBlock = getBlockType(7);

    // cout << fallingBlock->index << endl;
    // fallingBlock->rotate();
    // cout << fallingBlock->index << endl;
    cout << fallingBlock->getChar() << endl;

    // fallingBlock->rotate();
    // fallingBlock->rotate(); // this is just for resetting the rotation, or rotating back around
    // fallingBlock->rotate();

    // This is temporary, just to test and show how this will work
    // by getting the sprites of each block. It gets it at the index of its rotation
    // so by using rotate() first it will change which array it returns

    spawnBlock(board, fallingBlock);

    displayBoard(board);

    Game game;

    game.loadTextures();
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock

    float secondCounter = 0;

    while(!game.isDone())
    {
        sf::Time elapsedTime = clock.restart();
        secondCounter += elapsedTime.asSeconds();
        game.handleInput();
        game.update(board, fallingBlock);
        game.render(board);
        if(secondCounter >= 1) {
            fallingBlock->movePos(board, 0, 1);
            // displayBoard(board);
            secondCounter = 0;
        }
        sf::sleep(elapsedTime + TIME_PER_FRAME - clock.getElapsedTime());
    }

    return 0;

}