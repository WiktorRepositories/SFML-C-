#include "_include_definitions.h"
#ifdef INC_ABSTRACT_ENTHITY_H

#ifndef ABSTRACT_ENTHITY_H
#define ABSTRACT_ENTHITY_H

#include "SFML/Graphics.hpp"
#include "../constants/constatnts.h"

/*********************************************************************************
 * @name    Entity
 * @brief   Abstract class tht contain basic functionality for every derived ones
 */
class Entity
{
protected:
    sf::Sprite sprite;

    // Boolean member that track the enthity status
    bool _destroyed;

public:
    Entity(sf::Texture& reftexture): sprite(reftexture), _destroyed(false) {}
    virtual ~Entity(void) {}

    virtual void update(void) = 0;
    virtual void draw(sf::RenderWindow& refwindow) = 0;

    // Helper function to get the bounding box of a sprite
    sf::FloatRect getBoundingbox(void) const noexcept;

    // Helper function to get the center of a spreite
    sf::Vector2f getCenter(void) const noexcept;

    // Helper functions to get the position of the sprite
    float x(void) const noexcept;
    float y(void) const noexcept;

    // Helper functions to get the edges of the sprite
    float top(void) const noexcept;
    float bottom(void) const noexcept;
    float left(void) const noexcept;
    float right(void) const noexcept;

    // Functions for the state of enthetity
    void destroy(void) noexcept;
    bool isDestroyed(void) const noexcept;
};
//===============================================================================

#endif // ABSTRACT_ENTHITY_H
#endif // INC_ABSTRACT_ENTHITY_H