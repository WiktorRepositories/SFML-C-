#include "_include_definitions.h"
#ifdef INC_BACKGROUND_H

#include "abstract_entity.h"

/************************************************************************************
 * @name    Background
 * @brief   Placeholder derived class for managing external initialized sf::Texture
 */
class Background: public Entity
{
    sf::Texture& reftexture;

public:
    // Interface of the class
    // Arguments are the initial coordinates of the center in the background
    // SFML uses the computer graphic convention
    // (0,0) is left top
    Background(float x, float y, sf::Texture& texture);

    // Implement the pure virtual functions
    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;
};
//==================================================================================

#endif // INC_BACKGROUND_H