#include "_include_definitions.h"
#ifdef INC_BRICK_ENTHITY_H

#ifndef BRICK_ENTHITY_H
#define BRICK_ENTHITY_H

#include "abstract_entity.h"

// Class to represent a brick
// Inherits from Entity
// A grid of bircks is displayed across the top of acreen
// This grid will be represented by an std::vector of bricks objects
// When the ball hits a brick, the brick  is destroyed and disappears
// When a brick is destroyed, it is deleted from the vector
class Brick: public Entity
{
    sf::Texture* ptexture;
    int strenght = constants::brickStrenght;

public:
    Brick(float x, float y, sf::Texture* ptexture);
    ~Brick(void) { }

    void setStrenght(unsigned int n) noexcept;
    void weakenByAmount(unsigned int n) noexcept;
    bool isTopWeak(void) const noexcept;

    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;
};

#endif // BRICK_ENTHITY_H
#endif // INC_BRICK_ENTHITY_H