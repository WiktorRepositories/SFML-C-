#include "inc_project_info.h"
#ifdef INC_BALL_PADDLE_INTERACTION_H

#include "SFML/Graphics.hpp"
#include "constants/constatnts.h"
#include "iostream"

class Entity
{
protected:
    sf::Sprite& refsprite;

public:
    Entity(sf::Sprite& refsprite): refsprite(refsprite) { printf("Entity()\n"); }
    virtual ~Entity(void){;}

    virtual void update(void) = 0;
    virtual void draw(sf::RenderWindow& refwindow) = 0;

    // Helper function to get the bounding box of a sprite
    sf::FloatRect getBoundingbox(void) const noexcept;

    // Helper function to get the center of a spreite
    sf::Vector2f getCenter(void) const noexcept;

    // Helper functions to get the position of the sprite
    float x(void) const noexcept;
    float y(void) const noexcept;
};

class Background: public Entity
{
    sf::Texture& reftexture;

public:
    // Interface of the class
    // Arguments are the initial coordinates of the center in the background
    // SFML uses the computer graphic convention
    // (0,0) is left top
    Background(float x, float y, sf::Sprite& sprite, sf::Texture& texture);

    // Implement the pure virtual functions
    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;
};

class MovingEntity: public Entity
{
protected:
    sf::Vector2f velocity;

public:
    MovingEntity(sf::Sprite& refsprite): Entity(refsprite) { printf("MovingEntity()\n"); ;}

    // Helper function to change the sprite direction
    virtual void moveUp(void) noexcept = 0;
    virtual void moveLeft(void) noexcept = 0;
    virtual void moveRight(void) noexcept = 0;
};

class Ball: public MovingEntity
{
    sf::Texture& reftexture;

public:
    Ball(float x, float y, sf::Sprite& refsprite, sf::Texture& reftexture);

    void update(void) override;
    void draw(sf::RenderWindow& refwind) override;

    void moveUp(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};

class Paddle: public MovingEntity
{
    sf::Texture& reftexture;

    void processPlayerInput(void);

public:
    Paddle(float x, float y, sf::Sprite& refsprite, sf::Texture& reftexture);

    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;

    void moveUp(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};

/********************************************************************************
 * Interactions between classes
 */
// Determine wheather two entities overlap
bool IsInteracting(const Entity& refentA, const Entity& refentB);
// Resolve potential collision between the ball and the paddle
void HandleColision(Ball& refball, const Paddle& refpaddle);
//===============================================================================

void CALL_main(void);

#endif // INC_BALL_PADDLE_INTERACTION_H