#include "tetris.h"

int main() {

    char board[20][10];

    initializeBoard(board, '-');

    displayBoard(board);

    sf::RenderWindow window(sf::VideoMode(1024, 812), "Window name");
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                // Close window button clicked.
                window.close();
            }
            if (event.type == sf::Event::EventType::KeyPressed){

                if (event.key.code == sf::Keyboard::Left){
                    // Do something here
                }
                else if (event.key.code == sf::Keyboard::Right){
                    // Do something here
                }
                
            }
        }
        window.clear(sf::Color::Black);
        // Draw here.
        window.display();
    }

    return 0;

}