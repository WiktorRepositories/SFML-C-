#include "x14_e_bouncing_ball.h"
#ifdef INC_MOVING_BALL_H

//====================================================================================
// Helper function to get the bounding box of a sprite
sf::FloatRect Entity::getBoundingbox(void) const noexcept
{
    return refsprite.getGlobalBounds();
}
// Helper function to get the center of a spreite
sf::Vector2f Entity::getCenter(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    return box.getCenter();
}
// Helper functions to get the position of the sprite
float Entity::x(void) const noexcept
{
    return refsprite.getGlobalBounds().position.x;
}
float Entity::y(void) const noexcept
{
    return refsprite.getGlobalBounds().position.y;
}
//====================================================================================
Background::Background(float x, float y, sf::Sprite& refsprite, sf::Texture& reftexture): Entity(refsprite), reftexture(reftexture)
{
    refsprite.setPosition(sf::Vector2f(x,y));
}
void Background::update(void)
{
    ;
}
void Background::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(refsprite);
}
//=====================================================================================

//=====================================================================================
Ball::Ball(float x, float y,   sf::Sprite& refsprite, sf::Texture& reftexture): MovingEntity(refsprite), reftexture(reftexture)
{
    refsprite.setPosition(sf::Vector2f(x, y));
    velocity = sf::Vector2f(constants::ballSpeed, constants::ballSpeed);
}
void Ball::update(void)
{
    // Move the position of the ball
    refsprite.move(velocity);

    // Check is the ball has moved off the left hand side of the window
    // If so we change sign of the x component of the velocity
    // This will make appear to bounce back into window
    float _x = x();
    float _y = y();

    if( (_x < 0) || (_x > constants::windowWidth) ) 
        velocity.x = -velocity.x;

    if( (_y < 0)  || (_y > constants::windowHeight) )
        velocity.y = -velocity.y;
}
void Ball::draw(sf::RenderWindow& refwind)
{
    refwind.draw(refsprite);
}
//====================================================================================
void CALL_main(void)
{
    // sf::Vector2u is needed to initialize object, this is vetor of two variables
    sf::Vector2u modeSize(constants::windowWidth, constants::windowHeight);
    sf::RenderWindow gameWindow(sf::VideoMode(modeSize), constants::windowName);


    sf::Texture textureBackground;    
    if( !textureBackground.loadFromFile(constants::texturePath1) )
    {
        std::cout << "File background load fail: " << constants::texturePath1 << std::endl;
        gameWindow.close();
        return;
    }
    sf::Sprite spriteBackground(textureBackground);
    Background background(0.0, 0.0, spriteBackground, textureBackground);


    sf::Texture textureBall;    
    if( !textureBall.loadFromFile(constants::texturePath2) )
    {
        std::cout << "File ball load fail: " << constants::texturePath2 << std::endl;
        gameWindow.close();
        return;
    }
    sf::Sprite spriteBall(textureBall);
    Ball ball(constants::windowWidth/2, constants::windowHeight/2, spriteBall, textureBall);


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
        background.draw(gameWindow);

        // Display the updaed graphic
        ball.update();
        ball.draw(gameWindow);

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_MOVING_BALL_H