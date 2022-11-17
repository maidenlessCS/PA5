#include "tetris.h"

int main() {

    srand (time(NULL));

    char board[20][10];

    initializeBoard(board, '-');
    // board [4][5] = 'l';
    // board [4][6] = 'l';
    // board [4][7] = 'l';
    // board [5][7] = 'l';

    // board [5][5] = 's';
    // board [5][6] = 's';
    // board [6][5] = 's';
    // board [6][6] = 's';

    int spawnBlok = rand() % 7 + 1;

    Block *fallingBlock;

    if(spawnBlok == 1) {
        fallingBlock = new T;
    }
    else if(spawnBlok == 2) {
        fallingBlock = new L;
    }
    else {
        fallingBlock = new J;
    }

    cout << fallingBlock->index;
    fallingBlock->rotate();
    cout << fallingBlock->index;

    displayBoard(board);

    // int posX = 0;

    // sf::RectangleShape square(sf::Vector2f(20, 20));
    // square.setFillColor(sf::Color(100, 250, 50));

    // sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TETRIS");
    // while(window.isOpen())
    // {
    //     sf::Event event;
    //     while(window.pollEvent(event))
    //     {
    //         if(event.type == sf::Event::Closed)
    //         {
    //             // Close window button clicked.
    //             window.close();
    //         }
    //         if (event.type == sf::Event::EventType::KeyPressed){

    //             if (event.key.code == sf::Keyboard::Left){
    //                 // Do something here
    //                 if(posX > 0+5) {
    //                     posX-=5;
    //                 }
    //                 square.setPosition(sf::Vector2f(posX, square.getPosition().y));
    //             }
    //             else if (event.key.code == sf::Keyboard::Right) {
    //                 if(posX < WINDOW_SIZE_X-square.getSize().x - 5) {
    //                     posX+=5;
    //                 }
    //                 square.setPosition(sf::Vector2f(posX, square.getPosition().y));
    //                 // Do something here
    //             }
                
    //         }
    //     }
    //     window.clear(sf::Color::Black);
    //     // Draw here.
    //     window.draw(square);
    //     window.display();
    // }

    Game game;

    game.loadTextures();
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock
    while(!game.isDone())
    {
        sf::Time start = clock.restart();
        game.handleInput();
        game.update(board);
        game.render(board);
        sf::sleep(start + TIME_PER_FRAME - clock.getElapsedTime());
    }

    return 0;

}