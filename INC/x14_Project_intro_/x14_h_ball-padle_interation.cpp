#include "x14_h_ball-padle_interation.h"
#ifdef INC_BALL_PADDLE_INTERACTION_H

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

// Background class contrctuctor
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
void Ball::moveUp(void) noexcept
{
    velocity.y = -constants::ballSpeed;
}
void Ball::moveLeft(void) noexcept
{
    velocity.x = -constants::ballSpeed;
}
void Ball::moveRight(void) noexcept
{
    velocity.x = constants::ballSpeed;
}
//=====================================================================================

//=====================================================================================
Paddle::Paddle(float x, float y, sf::Sprite& refsprite, sf::Texture& reftexture): MovingEntity(refsprite), reftexture(reftexture)
{
    refsprite.setPosition(sf::Vector2f(x, y));
    // Initital 0.0 speed
    velocity = sf::Vector2f(0.0, 0.0);
    //refsprite.setOrigin(getCenter());
}
void Paddle::processPlayerInput(void)
{
    bool arrowLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool arrowRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    if(arrowLeft && !arrowRight)
    {
        if(x() >= 0) 
            velocity.x = -constants::paddleSpeed;
        else 
            velocity.x = 0;
    }
    else if(!arrowLeft && arrowRight)
    {
        if(x() <= constants::windowWidth) 
            velocity.x = constants::paddleSpeed;
        else 
            velocity.x = 0;
    }
    else
        velocity.x = 0;
}
void Paddle::update(void)
{
    processPlayerInput();
    refsprite.move(velocity);
}
void Paddle::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(refsprite);
}
void Paddle::moveUp(void) noexcept {;}
void Paddle::moveLeft(void) noexcept
{
    velocity.x = -constants::paddleSpeed;
}
void Paddle::moveRight(void) noexcept
{
    velocity.x = constants::paddleSpeed;
}
//====================================================================================

//====================================================================================

// Determine wheather two entities overlap
bool IsInteracting(const Entity& refentA, const Entity& refentB)
{
    sf::FloatRect boxA = refentA.getBoundingbox();
    sf::FloatRect boxB = refentB.getBoundingbox();
    // Rerturn values fron findIntersection is : std::optional<sf::FloatRect>
    if(boxA.findIntersection(boxB).has_value()) 
        return true;
    else 
        return false;
}
// Resolve potential collision between the ball and the paddle
void HandleColision(Ball& refball, const Paddle& refpaddle)
{
    if(IsInteracting(refball, refpaddle))
    {
        refball.moveUp();

        if(refball.x() < refpaddle.x()) refball.moveLeft();
        else refball.moveRight();
    }
}
//====================================================================================

//====================================================================================
void CALL_main(void)
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
    sf::Sprite spriteBackground(textureBackground);
    Background background(0.0, 0.0, spriteBackground, textureBackground);

    // Texture of a ball initialization and bound to class
    sf::Texture textureBall;    
    if( !textureBall.loadFromFile(constants::ballTexturePath) )
    {
        std::cout << "ERROR: File ball load fail: " << constants::ballTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    sf::Sprite spriteBall(textureBall);
    Ball ball(constants::windowWidth/2, constants::windowHeight/2, spriteBall, textureBall);

    // Paddle texture initializtion and bound to class
    sf::Texture texturePaddle;
    if( !texturePaddle.loadFromFile(constants::paddleTexturePath) )
    {
        std::cout << "ERROR: File paddle load fail: " << constants::paddleTexturePath << std::endl;
        gameWindow.close();
        return;
    }
    sf::Sprite spritePaddle(texturePaddle);
    Paddle paddle(constants::windowWidth/2, constants::windowHeight - constants::paddleHeight, spritePaddle, texturePaddle);


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
        HandleColision(ball, paddle);

        // Display the updaed graphic
        background.draw(gameWindow);
        ball.draw(gameWindow);
        paddle.draw(gameWindow);

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_BALL_PADDLE_INTERACTION_H