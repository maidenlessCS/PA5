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

void Game::update(char board[20][10], Block* fallingBlock) {
    
}

void Game::render(char board[20][10], Block* nextBlock) {

    // Basically it finds the center of the screen, then goes back half the size of the board from there
    // I know the multiplication could be simplified but it makes more sense when written this way
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(700, 650));
    background.setTexture(&back);
    mWindow.draw(background);

    drawHighscore();
    drawCurrentscore();

    sf::RectangleShape boardBorder;
    boardBorder.setSize(sf::Vector2f(((BLOCK_SIZE+BORDER_SIZE*2)*10)-1, ((BLOCK_SIZE+BORDER_SIZE*2)*20)-1));
    boardBorder.setPosition(sf::Vector2f(WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2, WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2));
    boardBorder.setFillColor(sf::Color(0,0,0,0));
    boardBorder.setOutlineColor(sf::Color(102,102,102));
    boardBorder.setOutlineThickness(2);
    mWindow.draw(boardBorder);

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
    next.setStyle(sf::Text::Bold | sf::Text::Underlined);
    next.setPosition(horizontalOffset/2 - 150/2, (WINDOW_SIZE_Y - WINDOW_SIZE_Y/2)-160/2);
    next.setCharacterSize(24);
    next.setFillColor(sf::Color::White);
    next.setOutlineColor(sf::Color(102,102,102));
    next.setOutlineThickness(2);
    mWindow.draw(next);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(BLOCK_SIZE+BORDER_SIZE*2, BLOCK_SIZE+BORDER_SIZE*2));
    square.setTexture(&art);
    square.setOutlineThickness(0);

    sf::RectangleShape emptySquare;
    emptySquare.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    emptySquare.setOutlineColor(sf::Color(60,60,60));
    emptySquare.setOutlineThickness(BORDER_SIZE);
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i<20; i++)
        {
            int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
            int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;

            char currentChar = board[i][j];
        
            if(currentChar == '-') {
                emptySquare.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i), 240));
                emptySquare.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2,   verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2);
                mWindow.draw(emptySquare);
            }
            else {
                squareColor(currentChar, square);
                square.setPosition(posX, posY);
                mWindow.draw(square);
            }
        }
    }
    horizontalOffset = (nextBox.getPosition().x - (BLOCK_SIZE+BORDER_SIZE*2)*nextBlock->getCenterX()) + (nextBox.getSize().x/2);
    verticalOffset = (nextBox.getPosition().y + 10 - (BLOCK_SIZE+BORDER_SIZE*2)*nextBlock->getCenterY()) + ((nextBox.getSize().y)/2);
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i< 5 ; i++)
        {
            int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
            int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;

            char currentChar = nextBlock->getSprite()[i][j];
            if(currentChar != '-' && !isdigit(currentChar)) {
                squareColor(currentChar, square);
                square.setPosition(posX, posY);
                mWindow.draw(square);
            }
        }
    }
    mWindow.display();
    mWindow.clear(sf::Color(10, 10, 10));
}

void Game::squareColor(char current, sf::RectangleShape &square){

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
            cout << "default ran" << endl;
    }
}

bool Game::isDone() const {
    return (!mWindow.isOpen() || mIsDone);
}

void Game::loadTextures() {
    if(!art.loadFromFile("squar.png")) {
        cout << "no squar" << endl;
        exit(11);
    }
    if(!back.loadFromFile("back.png")) {
        cout << "no back" << endl;
        exit(11);
    }
}

void Game::loadFont() {
    if (!font.loadFromFile("Excelsior.ttf"))
    {
        cout << "Font not found" <<endl;
    }
}

void Game::drawHighscore()
{
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

    std::ifstream file; 
    std::string Highscore;
    file.open("Highscore.txt");
    getline(file, Highscore);
    file.close();

    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 70));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset);
    scoreBox.setOutlineColor(sf::Color(102,102,102));
    scoreBox.setOutlineThickness(2);
    mWindow.draw(scoreBox);

    sf::Text high;
    high.setFont(font);
    high.setString("Highscore");
    high.setStyle(sf::Text::Bold | sf::Text::Underlined);
    high.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset);
    high.setCharacterSize(24);
    high.setFillColor(sf::Color::White);
    high.setOutlineColor(sf::Color(102,102,102));
    high.setOutlineThickness(2);
    mWindow.draw(high);
    
    sf::Text score;
    score.setFont(font);
    score.setString(Highscore);
    score.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset + 32);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color(102,102,102));
    score.setOutlineThickness(2);
    mWindow.draw(score);
}

void Game::getHighscore()
{
    std::ifstream file; 
    file.open("Highscore.txt");
    file >> highestScore;
    file.close();
}

void Game::checkScores()
{
    if (highestScore < round(currentScore))
    {
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

    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 70));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset + scoreBox.getSize().y + horizontalOffset/2 - 150/2);
    scoreBox.setOutlineColor(sf::Color(102,102,102));
    scoreBox.setOutlineThickness(2);
    mWindow.draw(scoreBox);

    sf::Text high;
    high.setFont(font);
    high.setString("Score");
    high.setStyle(sf::Text::Bold | sf::Text::Underlined);
    high.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset + scoreBox.getSize().y + horizontalOffset/2 - 150/2);
    high.setCharacterSize(24);
    high.setFillColor(sf::Color::White);
    high.setOutlineColor(sf::Color(102,102,102));
    high.setOutlineThickness(2);
    mWindow.draw(high);
    
    sf::Text score;
    score.setFont(font);
    score.setString(scoreToString(round(currentScore)));
    score.setPosition(horizontalOffset+(BLOCK_SIZE+BORDER_SIZE*2)*10 + horizontalOffset/2 - 150/2, verticalOffset + scoreBox.getSize().y + horizontalOffset/2 - 150/2 + 32);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color(102,102,102));
    score.setOutlineThickness(2);
    mWindow.draw(score);
}

void Game::explosion(char board[20][10])
{
    float scoredPoints = 100;
    bool explosion = false;
    int counter = 0;
    for(int i=0; i < 20; i++){
        if (board[i][0] != '-'){
            for (int j =0; j <10; j++)
            {
                if (board[i][j] == '-'){
                    counter = 0;
                    break;
                }
                else{
                counter++;
                }
                if (counter == 10){
                    for (int x=0; x <10; x++) {
                        for (int y =1; y <= i; y++){
                            board[i-y+1][x] = board[i-y][x];
                        }
                    }
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
    std::ostringstream os;
    os << score;
    return os.str();
}

void Game::gameEnd(char board[20][10], Block* fallingBlock)
{
    int count = 0;
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
    float scoredPoints = 20;
    currentScore += scoredPoints+(1-SPEED_MULT)*100;
    if(SPEED_MULT > 0.2) {
        SPEED_MULT -= (scoredPoints/5000);
    }
}