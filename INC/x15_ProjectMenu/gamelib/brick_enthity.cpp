#include "brick_enthity.h"
#ifdef INC_BRICK_ENTHITY_H

#ifndef BRICK_ENTHITY_CPP
#define BRICK_ENTHITY_CPP

// Format: RGBA
const sf::Color brickColorHit1{0x00, 0xFF, 0x00, 80}; // Dull green
const sf::Color brickColorHit2{0x00, 0xFF, 0x00, 170}; // Medium green
const sf::Color brickColorHit3{0x00, 0xFF, 0x00, 255}; // Bright green

/*********************************************************************************************************
 * @name Brick::Brick
 * @brief 
 */
Brick::Brick(float x, float y, sf::Texture* ptexture): Entity(*ptexture), ptexture(ptexture)
{
    sprite.setPosition(sf::Vector2f(x,y));
    //sprite.setOrigin(getCenter());
}
//========================================================================================================

/*********************************************************************************************************
 * @name Brick::draw
 * @brief 
 */
void Brick::setStrenght(unsigned int n) noexcept
{
    if(n <= constants::brickStrenght)
        strenght = n;
    else
        strenght = constants::brickStrenght;
}
//========================================================================================================

/*********************************************************************************************************
 * @name Brick::weakenByAmount
 * @brief 
 */
void Brick::weakenByAmount(unsigned int n) noexcept
{
    if( n <= constants::brickStrenght )
        strenght = strenght - n;
}
//========================================================================================================

/*********************************************************************************************************
 * @name Brick::isTopWeak
 * @brief   Value overlap to be max then 
 */
bool Brick::isTopWeak(void) const noexcept
{
    return strenght <= 0;
}
//========================================================================================================

/*********************************************************************************************************
 * @name Brick::update
 * @brief 
 */
void Brick::update(void)
{
    switch (strenght)
    {
    case 0x03:
        sprite.setColor(brickColorHit3);
        break;

    case 0x02:
        sprite.setColor(brickColorHit2);
        break;

    case 0x01:
        sprite.setColor(brickColorHit1);
        break;
    
    default:
        break;
    }
}
//========================================================================================================

/*********************************************************************************************************
 * @name Brick::draw
 * @brief 
 */
void Brick::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(sprite);
}
//========================================================================================================

#endif // BRICK_ENTHITY_CPP
#endif // INC_BRICK_ENTHITY_H