#include "inc_project_info.h"
#ifdef INC_BALL_BRICKS_INTERACTION_H

#include "SFML/Graphics.hpp"
#include "constants/constatnts.h"
#include "iostream"
#include "vector"
#include "algorithm"

class Entity
{
protected:
    sf::Sprite sprite;

    // Boolean member that track the enthity status
    bool _destroyed;

public:
    Entity(sf::Texture& reftexture): sprite(reftexture), _destroyed(false) {}
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

    // Helper functions to get the edges of the sprite
    float top(void) const noexcept;
    float bottom(void) const noexcept;
    float left(void) const noexcept;
    float right(void) const noexcept;

    // Functions for the state of enthetity
    void destroy(void) noexcept;
    bool isDestroyed(void) const noexcept;
};

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

class MovingEntity: public Entity
{
protected:
    sf::Vector2f velocity;

public:
    MovingEntity(sf::Texture& texture): Entity(texture) {}
    ~MovingEntity(void) {}

    // Helper function to change the sprite direction
    virtual void moveUp(void) noexcept = 0;
    virtual void moveLeft(void) noexcept = 0;
    virtual void moveRight(void) noexcept = 0;
};

class Ball: public MovingEntity
{
    sf::Texture& reftexture;

public:
    Ball(float x, float y, sf::Texture& reftexture);
    ~Ball(void) {}

    void update(void) override;
    void draw(sf::RenderWindow& refwind) override;

    void moveUp(void) noexcept;
    void moveDown(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};

class Paddle: public MovingEntity
{
    sf::Texture& reftexture;

    void processPlayerInput(void);

public:
    Paddle(float x, float y, sf::Texture& reftexture);
    ~Paddle(void) { }

    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;

    void moveUp(void) noexcept;
    void moveDown(void) noexcept;
    void moveLeft(void) noexcept;
    void moveRight(void) noexcept;
};

// Class to represent a brick
// Inherits from Entity
// A grid of bircks is displayed across the top of acreen
// This grid will be represented by an std::vector of bricks objects
// When the ball hits a brick, the brick  is destroyed and disappears
// When a brick is destroyed, it is deleted from the vector
class Brick: public Entity
{
    sf::Texture* ptexture;

public:
    Brick(float x, float y, sf::Texture* ptexture);
    ~Brick(void) { }

    void update(void) override;
    void draw(sf::RenderWindow& refwindow) override;
};

/********************************************************************************
 * Interactions between classes
 */
// Determine wheather two entities overlap
bool IsInteracting(const Entity& refentA, const Entity& refentB);
// Resolve potential collision between the ball and the paddle
void HandleColision(Ball& refball, const Paddle& refpaddle);
// Resolve potential collision between the ball and a brick
void HandleColision(Ball& refball, Brick& refbrick);
;//===============================================================================

void CALL_BallBricksInteractions_main(void);

#endif // INC_BALL_BRICKS_INTERACTION_H