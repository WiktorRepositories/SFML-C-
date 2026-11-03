#include "_include_definitions.h"
#ifdef INC_MOVING_ENTHITY_H

#ifndef MOVING_ENTHITY_H
#define MOVING_ENTHITY_H

#include "abstract_entity.h"

class MovingEntity: public Entity
{
protected:
    sf::Vector2f velocity;

public:
    MovingEntity(sf::Texture& texture): Entity(texture) {}
    ~MovingEntity(void) {}

    virtual void setPosition(float x, float y) noexcept = 0;
    virtual void setSpeed(float Vx, float Vy) noexcept = 0;

    // Helper function to change the sprite direction
    virtual void moveUp(void) noexcept = 0;
    virtual void moveLeft(void) noexcept = 0;
    virtual void moveRight(void) noexcept = 0;
};

#endif // MOVING_ENTHITY_H
#endif // INC_MOVING_ENTHITY_H