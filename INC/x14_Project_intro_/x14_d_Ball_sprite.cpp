#include "x14_d_Ball_sprite.h"
#ifdef INC_BALL_SPRITE_H

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
    refsprite.move(velocity);
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


    gameWindow.setFramerateLimit(1);

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

#endif // INC_BALL_SPRITE_H