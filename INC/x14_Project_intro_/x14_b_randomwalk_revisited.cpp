#include "x14_b_randomwalk_revisited.h"
#ifdef INC_RANDOM_WALK_REVISITED_H

Creature::Creature(float x, float y)
{
    velocity = sf::Vector2f(vx, vy);
    circle.setPosition(sf::Vector2(x, y));

    // Set the graphical properties
    circle.setRadius(5.0);
    circle.setFillColor(sf::Color::Red);
}

Creature::~Creature(void)
{
    ;
}

void Creature::draw(sf::RenderWindow& window)
{
    // Ask the window to draw the shape for us
    window.draw(circle);
}

// UPdate creature new position
void Creature::update(void)
{
    // Changes the direction of movement at random
    vx = bd(mt) ? vx : -vx;
    vy = bd(mt) ? vy : -vy;

    // MOve the creature to its new position
    circle.move(sf::Vector2(vx, vy));
}

std::mt19937 Creature::mt;
std::bernoulli_distribution Creature::bd;

void CALL_SFML_CircleInWindow(void)
{
    float width = constants::windowWidth / 2.0;     // Test Values
    float height = constants::windowHeight / 2.0;   // Test values
    Creature creature(width, height);

    // sf::Vector2u is needed to initialize object, this is vetor of two variables
    sf::Vector2u modeSize(constants::windowWidth, constants::windowHeight);
    sf::RenderWindow gameWindow(sf::VideoMode(modeSize), "Random Walk");

    gameWindow.setFramerateLimit(30);

    // Game loop 
    // Clear the screen 
    // Check for new events 
    // Calcuate the updates graphic 
    // Display the updates graphic
    while(gameWindow.isOpen())
    {
        // Clear screen
        gameWindow.clear(sf::Color::Black);

        
        // If the user pressed "Escape" or clicked close, we close the window
        // This will terminate the program
        // Check for and events since the last loop iteration
        // std::optional<sf::Event>, 
        while(const std::optional<sf::Event> event = gameWindow.pollEvent())
        {
            if(event->is<sf::Event::Closed>())   
            {
                gameWindow.close();
                break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) gameWindow.close();

        // Calculate the updated graphic 
        // This space left intentional black
        creature.update();
        creature.draw(gameWindow);

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_RANDOM_WALK_REVISITED_H

