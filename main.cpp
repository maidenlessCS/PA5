/**
 * @file main.cpp
 * @author Ben Bonus, Davin Lewis
 * @brief runs main function including main menu and Tetris game
 * @version 0.1
 * @date 2022-12-06
 */

#include "tetris.h"

int main() {
    bool gameRestarting = false;
    
    do {
        // sets the random seed to time(NULL), ensuring that it is actually random
        srand (time(NULL));
        //creates game, loads textures and fonts
        Game game;
        game.loadTextures();
        game.loadFont();
        // closes if either music file can't load
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
        // Main menu prototype
        bool gameStart = false;
        bool overPlayButton = false;
        bool overExitButton = false;
        // starts main menu music
        menuTheme.play();
        menuTheme.setLoop(true);
        // main menu loop, ends when game started (or exited)
        while(!gameStart)
        {
            //displays the main menu background
            game.mainMenuBackground();
            //displays the main menu buttons and functionality
            game.mainMenuButtons(gameStart, overPlayButton, overExitButton);
        }
        // ends main menu music
        menuTheme.stop();
        // gets highscore from text file
        game.getHighscore();
        // starts clock, running 60 fps
        char board[20][10];
        // sets board to all blanks spaces, or '-'
        initializeBoard(board, '-');
        // board for game to convert to sfml
        board[4][5] = 'T';
        // board to display next block on screen
        char nextBoard[5][5];

        // assigns fallingBlock to a random block type
        int randBlock = rand() % 7 + 1;
        Block *fallingBlock = nullptr;
        setBlockType(randBlock, fallingBlock);

        // assigns nextBlock to a random block type
        randBlock = rand() % 7 + 1;
        Block *nextBlock = nullptr;
        setBlockType(randBlock, nextBlock);
        // puts falling block at the top of the board
        spawnBlock(board, fallingBlock);
        // out's the board to the terminal
        displayBoard(board);
        // starts clock, running 60 fps
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
        sf::Clock clock; // starts the clock
        // integer tracks time passing
        float secondsCounter = 0;
        // variable for testing when a new block will spawn, starts at false
        bool newBlock = false;
        // plays game music on loop
        gameTheme.play();
        gameTheme.setLoop(true);
        while(!game.isDone())
        {
            sf::Time elapsedTime = clock.restart();
            // adds time between frames, essentially acting as a timer
            secondsCounter += elapsedTime.asSeconds();
            // handles keyboard input from the player as well as exiting
            newBlock = game.handleInput(board, fallingBlock);
            // runs once every SPEED_MULT seconds, starts at 1 and slowly decreases
            if(secondsCounter >= game.SPEED_MULT) {
                // moves the block downwards, runs the if statement if it returns false (unable to move)
                //                            or if newBlock is set to true
                if(!fallingBlock->movePos(board, 0, 1) || newBlock) {
                    newBlock = false;

                    // checks for possible explosions (full row clears) and rewards points if necessary
                    game.explosion(board);
                    game.placementPoints();

                    // Spawning new block
                    int randBlock = rand() % 7 + 1;
                    fallingBlock = nextBlock;
                    setBlockType(randBlock, nextBlock);
                    spawnBlock(board, fallingBlock);
                }
                //resets counter to run again
                secondsCounter = 0;
            }
            game.render(board, nextBlock, true);
            displayBoard(board);

            sf::sleep(elapsedTime + TIME_PER_FRAME - clock.getElapsedTime());

            game.gameEnd(board, fallingBlock);
        }

        // loop and function conditions
        bool buttonPressed = false;
        bool overRestartButton = false;
        bool overExitButton2 = false;
        while(!buttonPressed) {
            // draws finished game
            game.render(board, nextBlock, false);
            // draws a transparent square as well as the end title and buttons
            game.endBackground();
            // redraws the scores to be over the transparent square
            game.drawHighscore();
            game.drawCurrentscore();
            // handles restart and exit buttons on end screen
            game.endButtons(gameRestarting, buttonPressed, overRestartButton, overExitButton2);
            // if the exit button is pressed
            if(buttonPressed && !gameRestarting) {
                game.checkScores();
                //ends game music
                gameTheme.stop();
                delete fallingBlock;
                delete nextBlock;
            }
        }
        // will run again if the restart button is pressed, causing the game to restart
    } while(gameRestarting);

    return 0;
}