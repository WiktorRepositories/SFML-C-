#include "x14_c_sprite.h"
#ifdef INC_SPRITE_H

// Initialize static data
//sf::Texture Background::texture;
//Entity::sprite = sf::Sprite( texture );
//sf::Sprite Entity::sprite;

/*************************************************************
 * @brief Initialization object Background in posistion (x,y)
 * @param x Diagonal position
 * @param y Horizontal position
 */
Background::Background(float x, float y, sf::Texture& texture, sf::Sprite& sprite): texture(texture), sprite(sprite)
{
    sprite.setPosition(sf::Vector2f(x,y));
}
//==========================================================

/***********************************************************
 * @brief Compute background new position
 */
void Background::update(void)
{
    ;
}
//==========================================================

/***********************************************************
 * @brief 
 * @param refwindow Reference to initializef object of type sf::RenderStates
 */
void Background::draw(sf::RenderWindow& refwindow)
{
    refwindow.draw(sprite);
}
//===========================================================

void CALL_SFML_Sprite(void)
{
    // sf::Vector2u is needed to initialize object, this is vetor of two variables
    sf::Vector2u modeSize(constants::windowWidth, constants::windowHeight);
    sf::RenderWindow gameWindow(sf::VideoMode(modeSize), constants::windowName);

    sf::Texture texture;    
    if( !texture.loadFromFile(constants::texturePath) )
    {
        std::cout << "File load fail: " << constants::texturePath << std::endl;
        gameWindow.close();
        return;
    }
    sf::Sprite sprite(texture);
    Background background(0.0, 0.0, texture, sprite);

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
        background.update();
        background.draw(gameWindow);

        // Display the updated graphic
        gameWindow.display();
    }
}

#endif // INC_SPRITE_H