#include "x14_a_introduction.h"
#ifdef INC_PROJECT_INFO_H

using namespace std::literals;

void CALL_TestLibrary(void)
{
    // Create the game window using an object of class RenderWindow
    // The constructor takes an SFML 2D vector with the window dimension
    // and an std::string with the window title 
    // The SFML code is in the sf namespaces
    //sf::RenderWindow gameWindow{ {constants::windowWidth, constants::windowHeight}, "Simple Breakout Game Version 1"};
    sf::Vector2u modeSize(constants::windowWidth, constants::windowHeight);
    sf::RenderWindow gameWindow(sf::VideoMode(modeSize), constants::windowTitle);

    // Limit the frame rate 
    // This allows other procesess to run and reduce power consumption
    gameWindow.setFramerateLimit(30); // Max rate is 30 frames per second

    // Game loop 
    // Clear the screen 
    // Check for new events 
    // Calcuate the updates graphic 
    // Display the updates graphic
    while(gameWindow.isOpen())
    {
        // Clear screen
        gameWindow.clear(sf::Color::Black);

        
        // If the user pressed "Escape" or clicked close, we close the window
        // This will terminate the program
        // Check for and events since the last loop iteration
        while(const std::optional<sf::Event> event = gameWindow.pollEvent())
        {
            if(event->is<sf::Event::Closed>())   gameWindow.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) gameWindow.close();

        // Calculate the updated graphic 
        // This space left intentional black

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_PROJECT_INFO_H