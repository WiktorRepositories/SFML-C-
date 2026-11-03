#include "paddle_enthentity.h"
#ifdef INC_MOVING_PADDLE_H

#ifndef MOVING_PADDLE_CPP
#define MOVING_PADDLE_CPP

/*********************************************************************************************************
 * @name Paddle::Paddle
 * @brief 
 */
Paddle::Paddle(float x, float y, sf::Texture& reftexture): MovingEntity(reftexture), reftexture(reftexture)
{
    //sprite.setPosition(sf::Vector2f(x, y));
    //velocity = sf::Vector2f(0.0, 0.0);
    //sprite.setOrigin(getCenter());

    setPosition(x, y);
    setSpeed(0.0, 0.0);
}
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::Paddle
 * @brief 
 */
void Paddle::setPosition(float x, float y) noexcept
{
    sprite.setPosition(sf::Vector2f(x, y));
}
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::Paddle
 * @brief 
 */
void Paddle::setSpeed(float Vx, float Vy) noexcept
{
    velocity = sf::Vector2f(Vx, Vy);
}
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::processPlayerInput
 * @brief 
 */
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
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::update
 * @brief 
 */
void Paddle::update(void)
{
    processPlayerInput();
    sprite.move(velocity);
}
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::draw
 * @brief 
 */
void Paddle::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(sprite);
}
//========================================================================================================

/*********************************************************************************************************
 * @name Paddle::move...
 * @brief 
 */
void Paddle::moveUp(void) noexcept {}
void Paddle::moveDown(void) noexcept {}
void Paddle::moveLeft(void) noexcept    { velocity.x = -constants::paddleSpeed; }
void Paddle::moveRight(void) noexcept   { velocity.x =  constants::paddleSpeed; }
//========================================================================================================

#endif // MOVING_PADDLE_CPP
#endif // INC_MOVING_PADDLE_H