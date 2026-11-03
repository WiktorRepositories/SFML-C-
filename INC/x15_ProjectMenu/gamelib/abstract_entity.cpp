#include "abstract_entity.h"
#ifdef INC_ABSTRACT_ENTHITY_H

#ifndef ABSTRACT_ENTITY_CPP
#define ABSTRACT_ENTITY_CPP

#include "x_debug_functions.h"

/********************************************************************************
 * @name    sf::FloatRect Entity::getBoundingbox
 * @brief   Helper function to get the bounding box of a sprite
 */
sf::FloatRect Entity::getBoundingbox(void) const noexcept
{
    return sprite.getGlobalBounds();
}
//===============================================================================

/********************************************************************************
 * @name    sf::Vector2f Entity::getCenter
 * @brief   Helper function to get the center of a spreite
 */
sf::Vector2f Entity::getCenter(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    return box.getCenter();
}
//===============================================================================

/********************************************************************************
 * @name    Entity::x
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::x(void) const noexcept
{
    return sprite.getGlobalBounds().position.x;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::y
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::y(void) const noexcept
{
    return sprite.getGlobalBounds().position.y;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::top
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::top(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    //PrintRect(y(), box.size.y);
    return y() - box.size.y / 2.0;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::bottom
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::bottom(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    //PrintRect(y(), box.size.y);
    return y() + box.size.y / 2.0;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::left
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::left(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    //PrintRect(x(), box.size.x);
    return x() - box.size.x / 2.0;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::righ
 * @brief   Helper functions to get the position of the sprite
 */
float Entity::right(void) const noexcept
{
    sf::FloatRect box = getBoundingbox();
    //PrintRect(x(), box.size.x);
    return x() + box.size.x / 2.0;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::destroy
 * @brief   Helper functions to get the position of the sprite
 */
void Entity::destroy(void) noexcept
{
    _destroyed = true;
}
//===============================================================================

/********************************************************************************
 * @name    Entity::isDestroyed
 * @brief   Helper functions to get the position of the sprite
 */
bool Entity::isDestroyed(void) const noexcept
{
    return _destroyed;
}
//===============================================================================

#endif // ABSTRACT_ENTITY_CPP
#endif // INC_ABSTRACT_ENTHITY_H