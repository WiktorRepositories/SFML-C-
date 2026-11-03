#include "ball_enthetity.h"
#ifdef INC_BALL_ENTHITY_H

#ifndef BALL_ENTHITY_CPP
#define BALL_ENTHITY_CPP

/**********************************************************************************************************
 * @name    Ball::Ball
 * @brief   Initializer for Ball
 */
Ball::Ball(float x, float y, sf::Texture& reftexture): MovingEntity(reftexture), reftexture(reftexture)
{
    setPosition(x,y);
    setSpeed( constants::ballSpeed, constants::ballSpeed);
}
//=========================================================================================================

/**********************************************************************************************************
 * @name    Ball::setPosition
 * @brief   Initializer for Ball
 */
void Ball::setPosition(float x, float y) noexcept
{
    sprite.setPosition(sf::Vector2f(x, y));
    _destroyed = false;
}
//=========================================================================================================

/**********************************************************************************************************
 * @name    Ball::setSpeed
 * @brief   Initializer for Ball
 */
void Ball::setSpeed(float Vx, float Vy) noexcept
{
    velocity = sf::Vector2f(Vx, Vy);
}
//=========================================================================================================

/**********************************************************************************************************
 * @name    Ball::update
 * @brief   Refresh object method that display changed object
 */
void Ball::update(void)
{
    // Move the position of the ball
    sprite.move(velocity);

    // Check is the ball has moved off the left hand side of the window
    // If so we change sign of the x component of the velocity
    // This will make appear to bounce back into window
    float _x = x();
    float _y = y();

    if( (_x < 0) || (_x > constants::windowWidth) ) 
        velocity.x = -velocity.x;

    if(_y < 0)
        velocity.y = -velocity.y;

    // Ball hits botton of a acreen
    if(_y > constants::windowHeight)
    {
        velocity.y = -velocity.y;
        destroy();
    }
        
}
//=========================================================================================================

/**********************************************************************************************************
 * @name    Ball::Ball
 * @brief   Initializer for Ball
 */
void Ball::draw(sf::RenderWindow& refwind)  { refwind.draw(sprite); }
//=========================================================================================================

/**********************************************************************************************************
 * @name    Ball::Ball
 * @brief   Initializer for Ball
 */
void Ball::moveUp(void) noexcept    { velocity.y = -constants::ballSpeed; }
void Ball::moveDown(void) noexcept  { velocity.y =  constants::ballSpeed; }
void Ball::moveLeft(void) noexcept  { velocity.x = -constants::ballSpeed; }
void Ball::moveRight(void) noexcept { velocity.x =  constants::ballSpeed; }
//=========================================================================================================

#endif // BALL_ENTHITY_CPP
#endif // INC_BALL_ENTHITY_H