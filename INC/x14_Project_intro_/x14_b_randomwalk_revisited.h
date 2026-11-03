#include "inc_project_info.h"
#ifdef INC_RANDOM_WALK_REVISITED_H

#include "SFML/Graphics.hpp"
#include "string"
#include "random"
#include "constants/constatnts.h"

// Class to represent the creature moving around the screen
class Creature
{
    // Static random number engine and Bernoulli distribution objects
    static std::mt19937 mt;
    static std::bernoulli_distribution bd;

    // Define some properties oof the creature
    // SFML uses float intentionaly
    float vx = 4.0;
    float vy = 4.0;
    sf::Vector2f velocity;

    // We use the SFML CircleShape
    sf::CircleShape circle;
public:
    // Interface of the class

    // Constructor
    // Arguments are the initial coordinates of the centre of the ball 
    // SFML uses the cmputer graphic convention
    // 0,0 is the left top corner of the screen
    Creature(float x, float y);
    ~Creature(void);

    void draw(sf::RenderWindow& window);
    void update(void);
};

void CALL_SFML_CircleInWindow(void);

#endif // INC_RANDOM_WALK_REVISITED_H