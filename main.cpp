#include "tetris.h"

int main() {

    char board[20][10];

    initializeBoard(board, '-');

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
    
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Clock clock; // starts the clock
    while(!game.isDone())
    {
        sf::Time start = clock.restart();
        game.handleInput();
        game.update();
        game.render();
        sf::sleep(start + TIME_PER_FRAME - clock.getElapsedTime());
    }

    return 0;

}