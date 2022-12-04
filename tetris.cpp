#include "tetris.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS") {
    mIsDone = false;
}

void Game::handleInput(char board[20][10], Block* fallingBlock) {
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
                // This needs some work
                //
                // Probably change it so it changes the time needed to
                // drop block rather than just drop it manually
                //
                // fallingBlock->movePos(board, 0, 1);
            }
            else if (event.key.code == sf::Keyboard::Space) {
                bool canDrop = true;
                do {
                    canDrop = fallingBlock->movePos(board, 0, 1);
                } while(canDrop);
            }
        }
    }
}

void Game::update(char board[20][10], Block* fallingBlock) {
    
}

void Game::render(char board[20][10], Block* nextBlock) {
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(700, 650));
    background.setTexture(&back);
    mWindow.draw(background);
    drawHighscore();
    drawCurrentscore();
    sf::RectangleShape nextBox;
    nextBox.setSize(sf::Vector2f(150, 200));
    nextBox.setFillColor(sf::Color::Black);
    nextBox.setPosition(50, 250);
    mWindow.draw(nextBox);
    sf::Text next;
    next.setFont(font);
    next.setString("Next:");
    next.setPosition(50,250);
    next.setCharacterSize(24);
    next.setFillColor(sf::Color::White);
    mWindow.draw(next);

    // Basically it finds the center of the screen, then goes back half the size of the board from there
    // I know the multiplication could be simplified but it makes more sense when written this way
    int horizontalOffset = WINDOW_SIZE_X - WINDOW_SIZE_X/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*10)/2;
    int verticalOffset = WINDOW_SIZE_Y - WINDOW_SIZE_Y/2 - ((BLOCK_SIZE+BORDER_SIZE*2)*20)/2;

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
                        emptySquare.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i), 230));
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
    horizontalOffset = nextBox.getPosition().x+(nextBox.getSize().x - nextBox.getSize().x /2 - ((BLOCK_SIZE+BORDER_SIZE*2)*5)/2);
    verticalOffset = nextBox.getPosition().y+(nextBox.getSize().y  - nextBox.getSize().y /2 - ((BLOCK_SIZE+BORDER_SIZE*2)*5)/2);
        for (int j = 0; j < 5; j++)
            {
                for (int i = 0; i<5; i++)
                {
                    int posX = horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2 - BORDER_SIZE;
                    int posY = verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2 - BORDER_SIZE;

                    char currentChar = nextBlock->getSprite()[i][j];
                    cout << currentChar << " ";
                    if(currentChar == '-' || isdigit(currentChar)) {
                        emptySquare.setFillColor(sf::Color(40-(2*i),40-(2*i),40-(2*i), 230));
                        emptySquare.setPosition(horizontalOffset + BLOCK_SIZE*j+BORDER_SIZE*j*2,   verticalOffset + BLOCK_SIZE*i+BORDER_SIZE*i*2);
                        mWindow.draw(emptySquare);
                    }
                    else {
                        squareColor(currentChar, square);
                        square.setPosition(posX, posY);
                        mWindow.draw(square);
                    }
                }
                cout << endl;
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

void initializeBoard(char board[20][10], char fillChar) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            board[i][j] = fillChar;
        }
    }
}

void displayBoard(char board[20][10]) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

Block* getBlockType(int num) {
    Block *fallingBlock;
    switch(num) {
        case 1:
            fallingBlock = new T;
            break;
        case 2:
            fallingBlock = new O;
            break;
        case 3:
            fallingBlock = new J;
            break;
        case 4:
            fallingBlock = new L;
            break;
        case 5:
            fallingBlock = new I;
            break;
        case 6:
            fallingBlock = new Z;
            break;
        case 7:
            fallingBlock = new S;
            break;
        default:
            exit(2); // This shouldn't ever happen but just in case
            // fallingBlock = new T;
            // break;
    }
    return fallingBlock;
}

void spawnBlock(char board[20][10], Block* block) {
    vector<vector<char>> spriteSheet = block->getSprite();
    char blockChar = block->getChar();
    int start = block->getStartingRow();
    for(int i = 0; i < 5-start; i++) {
        for(int j = 0; j < 5; j++) {
            if(spriteSheet[i+start][j] == blockChar)
                board[i][2+j] = spriteSheet[i+start][j];
        }
    }
    block->posY = 2-start;
    block->posX = 4;
}

void Game::drawHighscore()
{
    std::ifstream file; 
    std::string Highscore;
    file.open("Highscore.txt");
    getline(file, Highscore);
    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 50));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(525, 100);
    mWindow.draw(scoreBox);
    sf::Text high;
    high.setFont(font);
    high.setString("Highscore:");
    high.setPosition(530,100);
    high.setCharacterSize(24);
    high.setFillColor(sf::Color::White);
    mWindow.draw(high);
    sf::Text score;
    score.setFont(font);
    score.setString(Highscore);
    score.setPosition(530,120);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    mWindow.draw(score);
}

void Game::drawCurrentscore()
{
    sf::RectangleShape scoreBox;
    scoreBox.setSize(sf::Vector2f(150, 50));
    scoreBox.setFillColor(sf::Color::Black);
    scoreBox.setPosition(525, 160);
    mWindow.draw(scoreBox);
    sf::Text high;
    high.setFont(font);
    high.setString("Score:");
    high.setPosition(530,160);
    high.setCharacterSize(24);
    high.setFillColor(sf::Color::White);
    mWindow.draw(high);
    sf::Text score;
    score.setFont(font);
    score.setString(scoreToString(currentScore));
    score.setPosition(530,180);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::White);
    mWindow.draw(score);
}

void Game::explosion(char board[20][10])
{
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
                    for (int x=0; x <10; x++){
                        for (int y =1; y <= i; y++){
                            board[i-y+1][x] = board[i-y][x];
                        }
                    }
                this->explosion(board);
                currentScore = currentScore+100;
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
    currentScore = currentScore+20;
}

// friend void rotate() {
//     index = (index + 1) % 4; // Wrap-around operation, increments from 0, 1, 2, 3 and then wraps back to 0
// }

// friend char getChar() { return mChar; }

// friend int getStartingRow() { return startRow; }

// friend vector<vector<char>> getSprite() {
//     vector<vector<char>> spriteArray(5, vector<char>(5));
//     for(int i = 0; i < 5; i++) {
//         for(int j = 0; j < 5; j++) {
//         spriteArray[i][j] = shape[index][i][j];
//         }
//     }
//     return spriteArray;
// }

// friend void movePos(char board[20][10], int moveX, int moveY) {
//     for(int i = -2; i < 3; i++) {
//         for(int j = -2; j < 3; j++) {
//         if(shape[index][i+2][j+2] != '-') {
//             board[posY+i][posX+j] = '-';
//         }
//         }
//     }
//     cout << "movePos ran" << endl;
//     posX += moveX;
//     posY += moveY;
//     for(int i = -2; i < 3; i++) {
//         for(int j = -2; j < 3; j++) {
//         board[posY+i][posX+j] = shape[index][i+2][j+2];
//         }
//     }
// }