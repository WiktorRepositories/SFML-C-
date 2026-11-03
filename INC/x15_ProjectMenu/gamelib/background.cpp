#include "background.h"
#ifdef INC_BACKGROUND_H

#ifndef BACKGROUND_H
#define BACKGROUND_H

// Background class contrctuctor
Background::Background(float x, float y, sf::Texture& reftexture): Entity(reftexture), reftexture(reftexture)
{
    sprite.setPosition(sf::Vector2f(x,y));
}
void Background::update(void)
{
    ;
}
void Background::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(sprite);
}
//=====================================================================================

#endif // BACKGROUND_H
#endif // INC_BACKGROUND_H
