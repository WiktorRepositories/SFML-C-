#include "_include_definitions.h"
#ifdef INC_MOVING_PADDLE_H

#ifndef MOVING_PADDLE_H
#define MOVING_PADDLE_H

#include "moving_enthity.h"

class Paddle: public MovingEntity
{
    sf::Texture& reftexture;

    void processPlayerInput(void);

public:
    Paddle(float x, float y, sf::Texture& reftexture);
    ~Paddle(void) { }

    void setPosition(float x, float y) noexcept;
    void setSpeed(float Vx, float Vy) noexcept;

    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;

    void moveUp(void) noexcept;
    void moveDown(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};

#endif // MOVING_PADDLE_H
#endif // INC_MOVING_PADDLE_H