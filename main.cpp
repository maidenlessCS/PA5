/**
 * @file main.cpp
 * @author Ben Bonus, Davin Lewis
 * @brief runs main function including main menu and Tetris game
 * @version 0.1
 * @date 2022-12-06
 */

#include "tetris.h"

int main() {
    //closes if music file can't load
    sf::Music gameTheme;
    if (!gameTheme.openFromFile("TetrisTheme.ogg")){
        cout << "no music" << endl;
        std::exit(0);
    }
    sf::Music menuTheme;
    if (!menuTheme.openFromFile("TetrisMenu.ogg")){
        cout << "no music" << endl;
        std::exit(0);
    }
    srand (time(NULL));
    //board for game to convert to sfml
    char board[20][10];
    //sets board to all blanks spaces
    initializeBoard(board, '-');
    //board to display next block
    char nextBoard[5][5];
    //picks a random block and random next block
    int randBlock = rand() % 7 + 1;
    Block *fallingBlock = getBlockType(1);
    randBlock = rand() % 7 + 1;
    Block *nextBlock = getBlockType(randBlock);
    //sets falling block to the top of the board
    spawnBlock(board, fallingBlock);
    //out's the board to the terminal
    displayBoard(board);
    //creates game, loads textures and fonts
    Game game;
    game.loadTextures();
    game.loadFont();
    //booleans to start game from main menu, and to check mouse locations
    bool gameStart = false;
    bool overPlayButton = false;
    bool overExitButton = false;
    //play main menu music on loop
    menuTheme.play();
    menuTheme.setLoop(true);
    while(!gameStart)
    {
        //displays the main menu background
        game.mainMenuBackground();
        //displays the main menu buttons and functionality
        game.mainMenuButtons(gameStart, overPlayButton, overExitButton);
        
    }
    //ends main menu music
    menuTheme.stop();
    //gets highscore from text file
    game.getHighscore();
    //starts clock, running 60 fps
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock
    //integer tracks time passing
    float secondsCounter = 0;
    bool newBlock = false;
    //plays game music on loop
    gameTheme.play();
    gameTheme.setLoop(true);

    while(!game.isDone())
    {
        sf::Time elapsedTime = clock.restart();
        secondsCounter += elapsedTime.asSeconds();
        //allows player to perform moves
        newBlock = game.handleInput(board, fallingBlock);
        //outputs the multiplyer speed to terminal
        cout << "speed mult: " << game.SPEED_MULT << endl;
        // runs every second
        if(secondsCounter >= game.SPEED_MULT) {
            //runs once the block hits the bottom or another block
            if(!fallingBlock->movePos(board, 0, 1) || newBlock) {
                newBlock = false;
                fallingBlock = nullptr;
                //checks for possible explosions and rewards points if necessary
                game.explosion(board);
                //gives points based on drop speed once block placed
                game.placementPoints();

                // Spawning new block
                int randBlock = rand() % 7 + 1;
                fallingBlock = nextBlock;
                nextBlock = getBlockType(randBlock);
                spawnBlock(board, fallingBlock);
            }
            //resets counter to run again
            secondsCounter = 0;
        }
        //renders game in sfml
        game.render(board, nextBlock);
        //displays board in terminal after changes
        displayBoard(board);
        sf::sleep(elapsedTime + TIME_PER_FRAME - clock.getElapsedTime());
        //checks if the game should end
        game.gameEnd(board, fallingBlock);
    }
    //compares highscore and current score then changes if necessary
    game.checkScores();
    //ends game music
    gameTheme.stop();
    return 0;
}