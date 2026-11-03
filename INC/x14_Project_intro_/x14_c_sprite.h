#include "inc_project_info.h"
#ifdef INC_SPRITE_H

#include "SFML/Graphics.hpp"
#include "constants/constatnts.h"
#include "iostream"

/*****************************************************************************************
 * Abstract class to represent any graphical entity on th screen
 */
class Entity
{
public:
    // Pure virtual functons
    // Concrete graphical entities must implement these functions
    // The update member function will cimpute the new position, appereance etc.
    // The draw member funtion will cause update objects o be displayed
    virtual void update(void) = 0;
    virtual void draw(sf::RenderWindow& refwindow) = 0;

    // virtual desctructor
    virtual ~Entity(void) {}
};
//======================================================================================

class Background: public Entity
{
    sf::Texture& texture;
    sf::Sprite& sprite;

public:
    // Interface of the class
    // Arguments are the initial coordinates of the center in the background
    // SFML uses the computer graphic convention
    // (0,0) is left top
    Background(float x, float y, sf::Texture& texture, sf::Sprite& sprite);

    // Implement the pure virtual functions
    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;
};

void CALL_SFML_Sprite(void);

#endif // INC_SPRITE_H