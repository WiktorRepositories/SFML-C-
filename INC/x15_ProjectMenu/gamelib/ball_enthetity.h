#include "_include_definitions.h"
#ifdef INC_BALL_ENTHITY_H

#ifndef BALL_ENTHITY_H
#define BALL_ENTHITY_H

#include "moving_enthity.h"

/************************************************************************************
 * @name    Ball
 * @brief   Placeholder derived class for managing external initialized sf::Texture
 */
class Ball: public MovingEntity
{
    sf::Texture& reftexture;

public:
    Ball(float x, float y, sf::Texture& reftexture);
    ~Ball(void) {}

    void setPosition(float x, float y) noexcept;
    void setSpeed(float Vx, float Vy) noexcept;

    void update(void) override;
    void draw(sf::RenderWindow& refwind) override;

    void moveUp(void) noexcept;
    void moveDown(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};
//====================================================================================

#endif // BALL_ENTHITY_H
#endif // INC_BALL_ENTHITY_H