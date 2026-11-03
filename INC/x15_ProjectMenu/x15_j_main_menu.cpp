#include "x15_j_main_menu.h"
#ifdef INC_X15_MAIN_CALL_MENU

#include "vector"
#include "algorithm"
#include "iostream"

#include "gamelib/abstract_entity.h"
#include "gamelib/background.h"
#include "gamelib/moving_enthity.h"
#include "gamelib/brick_enthity.h"
#include "gamelib/ball_enthetity.h"
#include "gamelib/objects_handlers.h"
#include "gamelib/paddle_enthentity.h"

void CALL_x15_j_main_menu(void)
{
    // Objects initializations

    // sf::Vector2u is needed to initialize object, this is vetor of two variables
    sf::Vector2u modeSize(constants::windowWidth, constants::windowHeight);
    sf::RenderWindow gameWindow(sf::VideoMode(modeSize), constants::windowTexturePath);

    // Texture Background initialization and bound to class
    sf::Texture textureBackground;    
    if( !textureBackground.loadFromFile(constants::windowTexturePath) )
    {
        std::cout << "ERROR: File background load fail: " << constants::windowTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    Background background(0.0, 0.0, textureBackground);

    // Texture of a ball initialization and bound to class
    sf::Texture textureBall;    
    if( !textureBall.loadFromFile(constants::ballTexturePath) )
    {
        std::cout << "ERROR: File ball load fail: " << constants::ballTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    Ball ball(constants::windowWidth/2, constants::windowHeight/2, textureBall);

    // Paddle texture initializtion and bound to class
    sf::Texture texturePaddle;
    if( !texturePaddle.loadFromFile(constants::paddleTexturePath) )
    {
        std::cout << "ERROR: File paddle load fail: " << constants::paddleTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    Paddle paddle(constants::windowWidth/2, constants::windowHeight - constants::paddleHeight, texturePaddle);

    // Brick testure initilization
    sf::Texture textureBrick;
    if( !textureBrick.loadFromFile(constants::brickTexturePath))
    {
        std::cout << "ERROR: File brick01 load fail: " << constants::brickTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    // Create the grid of bricks 
    // We will use an std::vector to store them
    std::vector<Brick> vecBricks;
    vecBricks.reserve(constants::bricksColumns * constants::bricksRows);
    for(unsigned int i=0; i<constants::bricksColumns; ++i)
    {
        for(unsigned int j=0; j<constants::bricksRows; ++j)
        {
            // Calculate the brick's position
            float x = constants::birckOffset + (i + 1)*constants::brickWidth;
            float y = (j + 1)*constants::brickHeight;
            // Create the brick object
            vecBricks.emplace_back(x, y, &textureBrick);
        }
    }
    // Frame amount 
    gameWindow.setFramerateLimit(10);

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
        // std::optional<sf::Event>, 
        while(const std::optional<sf::Event> event = gameWindow.pollEvent())
        {
            if(event->is<sf::Event::Closed>())   
            {
                gameWindow.close();
                break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) gameWindow.close();

        // Calculated the updated graphic
        background.update();
        ball.update();
        paddle.update();

        for(auto& i : vecBricks ) i.update();

        HandleColision(ball, paddle);
        // Check every brick for a colision wth ball
        for(auto& i : vecBricks ) HandleColision(ball, i);

        // Erase any destroyed bricks from grid
        // Remove if moves all lemets to back for which the conditional is true
        // It returns an iterator to the first moved element
        // We then call erase witch the iterator as argument
        // This will erase every eleent following this iterator
        auto lambdafun = [](const Brick& refbrick) {return refbrick.isDestroyed(); };
        vecBricks.erase(std::remove_if(std::begin(vecBricks), std::end(vecBricks), lambdafun), std::end(vecBricks));

        // Display the updaed graphic
        background.draw(gameWindow);
        ball.draw(gameWindow);
        paddle.draw(gameWindow);

        for(auto& i : vecBricks) i.draw(gameWindow);

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_BALL_BRICKS_INTERACTION_H