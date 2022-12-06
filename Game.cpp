/**
 * @file Game.cpp
 * @author Ben Bonus, Davin Lewis
 * @brief functions for the Game class in Tetris
 * @version 0.1
 * @date 2022-12-06
 */

#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    mIsDone = false;
}

bool Game::handleInput(char board[20][10], Block* fallingBlock) {
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
        if (event.type == sf::Event::EventType::KeyPressed){
            // LEFT ARROW PRESSED
            if (event.key.code == sf::Keyboard::Left){
                fallingBlock->movePos(board, -1, 0);
            }
            // RIGHT ARROW PRESSED
            else if (event.key.code == sf::Keyboard::Right) {
                fallingBlock->movePos(board, 1, 0);
            }
            else if (event.key.code == sf::Keyboard::Up) {
                fallingBlock->rotate(board);
            }
            else if (event.key.code == sf::Keyboard::Down) {
                // SPEED_MULT will never get below 0.2
                // It is using a > instead of a != simply because
                // != did not work. I assume it had something to do
                // with float innacurracy and very very small numbers
                // so this guarentee'd that it would test correctly
                if(SPEED_MULT > 0.11) {
                    TEMP_SPEED = SPEED_MULT;
                }
                
                SPEED_MULT = 0.1;
            }
            else if (event.key.code == sf::Keyboard::Space) {
                bool canDrop = true;
                do {
                    canDrop = fallingBlock->movePos(board, 0, 1);
                } while(canDrop);
                return true;
            }
        }
        if(event.type == sf::Event::EventType::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down) {
                SPEED_MULT = TEMP_SPEED;
            }
        }
    }
    return false;
}

void Game::render(char board[20][10], Block* nextBlock, bool clearSceen) {

    // Basically it finds the center of the screen, then goes back half the size of the board from there
    // I know the multiplication could be simplified but it makes more sense when written this way
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;
    //draws the background of the game
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(700, 650));
    background.setTexture(&back);
    mWindow.draw(background);
    //draws and positions the highscore and current score
    drawHighscore();
    drawCurrentscore();
    //draws and positions border to game board
    sf::RectangleShape boardBorder;
    boardBorder.setSize(sf::Vector2f(((BLOCK_SIZE+BORDER_SIZE*2)*10)-1, ((BLOCK_SIZE+BORDER_SIZE*2)*20)-1));
    boardBorder.setPosition(sf::Vector2f(WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2, WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2));
    boardBorder.setFillColor(sf::Color(0,0,0,0));
    boardBorder.setOutlineColor(sf::Color(102,102,102));
    boardBorder.setOutlineThickness(2);
    mWindow.draw(boardBorder);
    //draws and positions the box and text for the next block
    sf::RectangleShape nextBox;
    nextBox.setSize(sf::Vector2f(150, 160));
    nextBox.setFillColor(sf::Color::Black);
    nextBox.setOutlineColor(sf::Color(102,102,102));
    nextBox.setOutlineThickness(2);
    nextBox.setPosition(horizontalOffset/2 - 150/2, (WINDOW_SIZE_Y - WINDOW_SIZE_Y/2)-160/2);
    mWindow.draw(nextBox);
    sf::Text next;
    next.setFont(font);
    next.setString("Next");
    next.setStyle(sf::Text::Bold);
    next.setCharacterSize(24);
    sf::FloatRect textRect = next.getLocalBounds();
    next.setPosition(sf::Vector2f(nextBox.getPosition().x+((nextBox.getSize().x-textRect.width)*.5), nextBox.getPosition().y));
    next.setFillColor(sf::Color::White);
    next.setOutlineColor(sf::Color(102,102,102));
    next.setOutlineThickness(2);
    mWindow.draw(next);
    //creates the base format for a solid square
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(BLOCK_SIZE+BORDER_SIZE*2, BLOCK_SIZE+BORDER_SIZE*2));
    square.setTexture(&art);
    square.setOutlineThickness(0);
    //creates the base format for a blank square
    sf::RectangleShape emptySquare;
    emptySquare.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    emptySquare.setOutlineColor(sf::Color(60,60,60));
    emptySquare.setOutlineThickness(BORDER_SIZE);
    //draws the game board
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i<20; i++)
        {
            //moves square to use one square to draw entire board
            int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
            int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;
            //gets character from current position on board
            char currentChar = board[i][j];
            //draws blanks square
            if(currentChar == '-') {
                emptySquare.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i), 240));
                emptySquare.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2,   verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2);
                mWindow.draw(emptySquare);
            }
            //draws a solid square
            else {
                squareColor(currentChar, square);
                square.setPosition(posX, posY);
                mWindow.draw(square);
            }
        }
    }
    horizontalOffset = (nextBox.getPosition().x - (BLOCK_SIZE+BORDER_SIZE*2)*nextBlock->getCenterX()) + (nextBox.getSize().x/2);
    verticalOffset = (nextBox.getPosition().y + 10 - (BLOCK_SIZE+BORDER_SIZE*2)*nextBlock->getCenterY()) + ((nextBox.getSize().y)/2);
    //draws the next block
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i< 5 ; i++)
        {
            int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
            int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;
            //draws solid squares based on the next block
            char currentChar = nextBlock->getSprite()[i][j];
            if(currentChar != '-' && !isdigit(currentChar)) {
                squareColor(currentChar, square);
                square.setPosition(posX, posY);
                mWindow.draw(square);
            }
        }
    }
    if(clearSceen) {
        mWindow.display();
        mWindow.clear(sf::Color(10, 10, 10));
    }
}

void Game::squareColor(char current, sf::RectangleShape &square){
    //sets square color based on the symbol in game board
    switch(current) {
        case 'T':
            square.setFillColor(sf::Color(160,0,240));
            break;
        case 'O':
            square.setFillColor(sf::Color(240,240,0));
            break;
        case 'J':
            square.setFillColor(sf::Color(0,0,240));
            break;
        case 'L':
            square.setFillColor(sf::Color(240,160,0));
            break;
        case 'I':
            square.setFillColor(sf::Color(0,240,240));
            break;
        case 'Z':
            square.setFillColor(sf::Color(240,0,0));
            break;
        case 'S':
            square.setFillColor(sf::Color(0,240,0));
            break;
        default: // Essentially the "else"
            // This is only in the loop because it uses i
            break;
    }
}

bool Game::isDone() const {
    return (!mWindow.isOpen() || mIsDone);
}

void Game::loadTextures() {
    //loads game textures, exits if errors
    if(!art.loadFromFile("squar.png")) {
        cout << "no squar" << endl;
        exit(11);
    }
    if(!back.loadFromFile("back.png")) {
        cout << "no back" << endl;
        exit(11);
    }
    if(!back2.loadFromFile("back2.png")) {
        cout << "no back2" << endl;
        exit(11);
    }
    if(!Title.loadFromFile("TetrisTitle.png")) {
        cout << "no title" << endl;
        exit(11);
    }
}

void Game::loadFont() {
    //loads font for the game, exits if errors
    if (!font.loadFromFile("Excelsior.ttf"))
    {
        cout << "Font not found" <<endl;
    }
}

void Game::drawHighscore()
{
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;
    //gets highscore from file
    std::ifstream file; 
    std::string readScore, highscore;
    file.open("Highscore.txt");
    getline(file, readScore);
    file.close();

    for(int i = 0; i < 10 - readScore.length(); i++) {
        highscore += '0';
    }
    highscore += readScore;
    
    //draws box for highscore
    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 70));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset);
    scoreBox.setOutlineColor(sf::Color(102,102,102));
    scoreBox.setOutlineThickness(2);
    mWindow.draw(scoreBox);
    //draws highscore text
    sf::Text high;
    high.setFont(font);
    high.setString("Highscore");
    high.setStyle(sf::Text::Bold);
    high.setCharacterSize(24);
    sf::FloatRect textRect = high.getLocalBounds();
    high.setPosition(sf::Vector2f(scoreBox.getPosition().x+((scoreBox.getSize().x-textRect.width)*.5), scoreBox.getPosition().y));
    high.setFillColor(sf::Color::White);
    high.setOutlineColor(sf::Color(102,102,102));
    high.setOutlineThickness(2);
    mWindow.draw(high);
    //draws actual highscore
    sf::Text score;
    score.setFont(font);
    score.setString(highscore);
    score.setCharacterSize(24);
    sf::FloatRect textRect2 = score.getLocalBounds();
    score.setPosition(sf::Vector2f(scoreBox.getPosition().x+((scoreBox.getSize().x-textRect2.width)*.5)-2, scoreBox.getPosition().y+32));
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color(102,102,102));
    score.setOutlineThickness(1);
    mWindow.draw(score);
}

void Game::getHighscore()
{
    // gets highscore to compare numerically
    std::ifstream file; 
    file.open("Highscore.txt");
    file >> highestScore;
    file.close();
}

void Game::checkScores()
{
    // checks if current score is more than highscore
    if (highestScore < round(currentScore))
    {
        // sets highscore to new score 
        std::ofstream file; 
        file.open("Highscore.txt");
        file << round(currentScore);
        file.close();
    }
}

void Game::drawCurrentscore()
{
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;
    //draws box for current score
    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 70));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset + scoreBox.getSize().y + horizontalOffset/2 - 150/2);
    scoreBox.setOutlineColor(sf::Color(102,102,102));
    scoreBox.setOutlineThickness(2);
    mWindow.draw(scoreBox);
    //draws "score" text
    sf::Text current;
    current.setFont(font);
    current.setString("Score");
    current.setStyle(sf::Text::Bold);
    current.setCharacterSize(24);
    sf::FloatRect textRect = current.getLocalBounds();
    current.setPosition(sf::Vector2f(scoreBox.getPosition().x+((scoreBox.getSize().x-textRect.width)*.5), scoreBox.getPosition().y));
    current.setFillColor(sf::Color::White);
    current.setOutlineColor(sf::Color(102,102,102));
    current.setOutlineThickness(2);
    mWindow.draw(current);
    //draws actual current score
    sf::Text score;
    score.setFont(font);
    score.setString(scoreToString(round(currentScore)));
    score.setCharacterSize(24);
    sf::FloatRect textRect2 = score.getLocalBounds();
    score.setPosition(sf::Vector2f(scoreBox.getPosition().x+((scoreBox.getSize().x-textRect2.width)*.5)-2, scoreBox.getPosition().y+31));
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color(102,102,102));
    score.setOutlineThickness(1);
    mWindow.draw(score);
}

void Game::explosion(char board[20][10])
{
    //base score for an explosion
    float scoredPoints = 100;
    //boolean to
    bool explosion = false;
    int counter = 0;
    for(int i=0; i < 20; i++){
        //if current space in array is solid square
        if (board[i][0] != '-'){
            for (int j =0; j <10; j++)
            {
                //if any space in that row is empty, breaks loops and resets counter
                if (board[i][j] == '-'){
                    counter = 0;
                    break;
                }
                else{
                    //counter goes up every solid square space in a row
                    counter++;
                }
                //if entire row is full of solid squares
                if (counter == 10){
                    for (int x=0; x <10; x++) {
                        for (int y =1; y <= i; y++){
                            //sets current row to row above
                            board[i-y+1][x] = board[i-y][x];
                        }
                    }
                    //checks for any other explosions
                    this->explosion(board);
                    currentScore += scoredPoints+(1-SPEED_MULT)*100;
                    if(SPEED_MULT > 0.2) {
                        SPEED_MULT -= (scoredPoints/5000);
                    }
                }
            }
        }
    }
}

std::string Game::scoreToString(int score)
{
    //returns score as text
    std::ostringstream os;
    for(int i = 0; i < 10 - std::to_string(score).length(); i++) {
        os << '0';
    }
    os << score;
    return os.str();
}

void Game::gameEnd(char board[20][10], Block* fallingBlock)
{
    int count = 0;
    //checks across the board is there is a block at the top of the board and new block
    //cannot move down, ends game if both are true
    while (count < 10){
        if (board[0][count] != '-' && !fallingBlock->movePos(board, 0, 1))
        {
            mIsDone = true;
        }
        count++;
    }
}

void Game::placementPoints()
{
    //base point score
    float scoredPoints = 20;
    currentScore += scoredPoints+(1-SPEED_MULT)*100;
    if(SPEED_MULT > 0.2) {
        SPEED_MULT -= (scoredPoints/5000);
    }
}

void Game::mainMenuBackground(){
    //actual background design
    sf::RectangleShape menuBackground;
    menuBackground.setSize(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
    menuBackground.setTexture(&back2);
    mWindow.draw(menuBackground);
    //darkens the background for asthetics
    sf::RectangleShape blackground;
    blackground.setSize(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
    blackground.setFillColor(sf::Color(0,0,0,160));
    mWindow.draw(blackground);
    
    sf::RectangleShape title;
    int titlePosX = WINDOW_SIZE_X - WINDOW_SIZE_X/2;
    int titlePosY = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - WINDOW_SIZE_Y/4;
    title.setSize(sf::Vector2f(984/1.75, 168/1.75));
    title.setTexture(&Title);
    title.setOrigin(title.getSize().x/2, title.getSize().y/2);

    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(titlePosX + 12, titlePosY + 8));
    mWindow.draw(title);

    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(titlePosX, titlePosY));
    mWindow.draw(title);
}

void Game::mainMenuButtons(bool &gameStart, bool &overPlayButton,bool &overExitButton){
    //designs and positions the "play" button
    sf::RectangleShape playButton;
    playButton.setSize(sf::Vector2f(150,75));
    playButton.setOrigin(playButton.getSize().x/2, playButton.getSize().y/2);
    playButton.setPosition(sf::Vector2f(WINDOW_SIZE_X - WINDOW_SIZE_X/2,WINDOW_SIZE_Y - WINDOW_SIZE_Y/2));
    playButton.setOutlineThickness(5);
    playButton.setFillColor(sf::Color(34,59,140, 230));
    playButton.setOutlineColor(sf::Color(0,0,0,230));
    //designs and positions the "exit" button
    sf::RectangleShape exitButton;
    exitButton.setSize(sf::Vector2f(150,75));
    exitButton.setOrigin(exitButton.getSize().x/2, exitButton.getSize().y/2);
    exitButton.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y+WINDOW_SIZE_Y/6));
    exitButton.setOutlineThickness(5);

    sf::RectangleShape title;
    title.setSize(sf::Vector2f(984/1.75, 168/1.75));
    title.setTexture(&Title);
    title.setOrigin(title.getSize().x/2, title.getSize().y/2);
    title.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y-WINDOW_SIZE_Y/4));
    mWindow.draw(title);

    sf::Text play;
    sf::Text exit;
    //designs and positions "play" and "exit" text
    play.setFillColor(sf::Color(0,0,0,230));
    playButton.setOutlineColor(sf::Color(0,0,0,230));

    exitButton.setFillColor(sf::Color(223,18,18, 230));  
    exit.setFillColor(sf::Color(0,0,0,230));
    exitButton.setOutlineColor(sf::Color(0,0,0,230));

    
    play.setCharacterSize(35);
    play.setFont(font);
    play.setString("Plae"); // The reason for this is because the 'y' throws off the centering
                            // even though it technically is properly centered, it looks too high
                            // because the y goes further below the other characters
                            // so we set localbounds without a y first and then change it after
    sf::FloatRect textRect = play.getLocalBounds();
    play.setString("Play");
    play.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
    play.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y));
    

    exit = play;
    exit.setString("Exit");
    textRect = exit.getLocalBounds();
    exit.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
    exit.setPosition(sf::Vector2f(playButton.getPosition().x, playButton.getPosition().y+WINDOW_SIZE_Y/6));

    sf::Event event;
    while(mWindow.pollEvent(event)){
        //closes window and applications if x button is hit
        if (event.type == sf::Event::Closed){
            mWindow.close();
            std::exit(0);
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
        bool mouseInPlayButton =    mousePosition.x >= playButton.getPosition().x - playButton.getSize().x/2
                                && mousePosition.x <= playButton.getPosition().x + playButton.getSize().x/2
                                && mousePosition.y >= playButton.getPosition().y - playButton.getSize().y/2
                                && mousePosition.y <= playButton.getPosition().y + playButton.getSize().y/2;
        bool mouseInExitButton =    mousePosition.x >= exitButton.getPosition().x - exitButton.getSize().x/2
                                && mousePosition.x <= exitButton.getPosition().x + exitButton.getSize().x/2
                                && mousePosition.y >= exitButton.getPosition().y - exitButton.getSize().y/2
                                && mousePosition.y <= exitButton.getPosition().y + exitButton.getSize().y/2;
    //when mouse is moved, gets checked if it's inside one of the buttons
    if(event.type == sf::Event::MouseMoved)
        {
            overPlayButton = mouseInPlayButton;
            overExitButton = mouseInExitButton;
        }
        //checks if one of buttons is clicked
        if (event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    //starts game is "play" is pressed
                    if(mouseInPlayButton){
                        gameStart = true;
                    }
                    //closes window and ends program is exit is pressed
                    if(mouseInExitButton){
                        mWindow.close();
                        std::exit(0);
                    }
                }
            }
    }
    //changes buttons color if being hovered over 
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
    //draws buttons with text
    mWindow.draw(playButton);
    mWindow.draw(exitButton);
    mWindow.draw(play);
    mWindow.draw(exit);


    mWindow.display();
    mWindow.clear(sf::Color(10, 10, 10));
}

void Game::endBackground(){
    //actual background design
    sf::RectangleShape blackground;
    blackground.setSize(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y));
    blackground.setFillColor(sf::Color(0,0,0,220));
    mWindow.draw(blackground);
}

void Game::endButtons(bool &restartPressed, bool &buttonPressed, bool &overRestartButton,bool &overExitButton) {

    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 + ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

    sf::RectangleShape restartButton;
    restartButton.setSize(sf::Vector2f(150,75));
    restartButton.setOrigin(restartButton.getSize().x/2, restartButton.getSize().y/2);
    restartButton.setPosition(sf::Vector2f(horizontalOffset + (WINDOW_SIZE_X-horizontalOffset)/2, WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 + restartButton.getSize().y/2));
    restartButton.setOutlineThickness(5);

    sf::RectangleShape exitButton;
    exitButton.setSize(sf::Vector2f(150,75));
    exitButton.setOrigin(exitButton.getSize().x/2, exitButton.getSize().y/2);
    exitButton.setPosition(sf::Vector2f(restartButton.getPosition().x, restartButton.getPosition().y+WINDOW_SIZE_Y/6));
    exitButton.setOutlineThickness(5);

    sf::Text restart;
    sf::Text exit;

    restartButton.setFillColor(sf::Color(34,59,140, 230));  
    restart.setFillColor(sf::Color(0,0,0,230));
    restartButton.setOutlineColor(sf::Color(0,0,0,230));

    exitButton.setFillColor(sf::Color(223,18,18, 220));  
    exit.setFillColor(sf::Color(0,0,0,230));
    exitButton.setOutlineColor(sf::Color(0,0,0,230));

    restart.setCharacterSize(35);
    restart.setFont(font);
    restart.setString("Restart");
    sf::FloatRect textRect = restart.getLocalBounds();
    restart.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
    restart.setPosition(sf::Vector2f(restartButton.getPosition().x, restartButton.getPosition().y));

    exit = restart;

    exit.setString("Exit");
    textRect = exit.getLocalBounds();
    exit.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
    exit.setPosition(sf::Vector2f(restartButton.getPosition().x, restartButton.getPosition().y+WINDOW_SIZE_Y/6));

    sf::Text gameOver;

    gameOver.setFillColor(sf::Color(223,18,18, 220));
    gameOver.setOutlineColor(sf::Color(240, 235, 235, 240));
    gameOver.setOutlineThickness(1);
    gameOver.setCharacterSize(60);
    gameOver.setFont(font);
    gameOver.setString("Game Over");
    gameOver.setStyle(sf::Text::Bold);
    textRect = gameOver.getLocalBounds();
    gameOver.setOrigin(sf::Vector2f(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f));
    gameOver.setPosition(sf::Vector2f(restartButton.getPosition().x/2.2, WINDOW_SIZE_Y/2));

    sf::Event event;
    while(mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            mWindow.close();
            std::exit(0);
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
        bool mouseInRestartButton= mousePosition.x >= restartButton.getPosition().x - restartButton.getSize().x/2
                                && mousePosition.x <= restartButton.getPosition().x + restartButton.getSize().x/2
                                && mousePosition.y >= restartButton.getPosition().y - restartButton.getSize().y/2
                                && mousePosition.y <= restartButton.getPosition().y + restartButton.getSize().y/2;
        bool mouseInExitButton =    mousePosition.x >= exitButton.getPosition().x - exitButton.getSize().x/2
                                && mousePosition.x <= exitButton.getPosition().x + exitButton.getSize().x/2
                                && mousePosition.y >= exitButton.getPosition().y - exitButton.getSize().y/2
                                && mousePosition.y <= exitButton.getPosition().y + exitButton.getSize().y/2;
    if(event.type == sf::Event::MouseMoved)
        {
            overRestartButton = mouseInRestartButton;
            overExitButton = mouseInExitButton;
        }
        if (event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(mouseInRestartButton) {
                        buttonPressed = true;
                        restartPressed = true;
                    }
                    if(mouseInExitButton) {
                        buttonPressed = true;
                        restartPressed = false;
                        // mWindow.close();
                        // std::exit(0);
                    }
                }
            }
    }

    if (overRestartButton){
        restartButton.setFillColor(sf::Color(152,181,227, 230));
        restart.setFillColor(sf::Color(255,255,255,230));
        restartButton.setOutlineColor(sf::Color(255,255,255,230));
    }
    else if (overExitButton){
        exitButton.setFillColor(sf::Color(255,65,65, 230));
        exit.setFillColor(sf::Color(255,255,255,230));
        exitButton.setOutlineColor(sf::Color(255,255,255,230));
    }

    mWindow.draw(restartButton);
    mWindow.draw(exitButton);
    mWindow.draw(restart);
    mWindow.draw(exit);
    mWindow.draw(gameOver);

    mWindow.display();
    mWindow.clear(sf::Color(10, 10, 10));
}