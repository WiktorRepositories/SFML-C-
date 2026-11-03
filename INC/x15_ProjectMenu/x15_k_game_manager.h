#include "gamelib/_include_definitions.h"
#ifdef INC_GAME_MANAGER_H

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "vector"
#include "algorithm"
#include "iostream"

#include "constants/constatnts.h"
#include "gamelib/abstract_entity.h"
#include "gamelib/background.h"
#include "gamelib/moving_enthity.h"
#include "gamelib/brick_enthity.h"
#include "gamelib/ball_enthetity.h"
#include "gamelib/objects_handlers.h"
#include "gamelib/paddle_enthentity.h"

/***************************************************************************************************************************
 * Member to store the current state of the game
 */
enum class EGameState
{
    ERROR,
    STARTING,
    PAUSED,
    RUNNING,
    GAME_OVER,
    PLAYER_WINS
};
//=========================================================================================================================

sf::Texture TextureCreator(const char* path, const char* errorMessage);
sf::Font FontCreator(const char* path, const char* errorMessage);

bool DetectRisingEdge(bool input, bool& laststate);
bool DetectFallingEdge(bool input, bool& laststate);

/******************************************************************************************************************
 * @brief   Game variables initialization class
 *          Privates variables are default initialized
 */
class GameManager
{
    // Default initialization of a gamewindow object
    sf::RenderWindow gameWindow = 
        sf::RenderWindow( 
            sf::VideoMode(sf::Vector2u(constants::windowWidth, constants::windowHeight)), 
            constants::windowTexturePath 
        );

    // Texture Background initialization and bound to class
    sf::Texture textureBackgrount = TextureCreator(constants::windowTexturePath, constants::windowErrorMessage );
    Background background = Background(0.0, 0.0, textureBackgrount);

    // Paddle texture initializtion and bound to class
    sf::Texture texturePaddle = TextureCreator(constants::paddleTexturePath, constants::windowErrorMessage );
    Paddle paddle = Paddle(constants::windowWidth/2, constants::windowHeight - constants::paddleHeight, texturePaddle);

    // Texture of a ball initialization and bound to class
    sf::Texture textureBall = TextureCreator(constants::ballTexturePath, constants::ballErrorMessage );
    Ball ball = Ball(constants::windowWidth/2, constants::windowHeight/2, textureBall);

    // Brick testure initilization
    sf::Texture textureBrick = TextureCreator(constants::brickTexturePath, constants::brickTexturePath );
    // Create the grid of bricks 
    // We will use an std::vector to store them
    std::vector<Brick> vecBricks;

    // Enumarate state machine that game is currently on
    enum EGameState enumState = EGameState::STARTING;

    // Amount of lives for a ball that drop below paddle
    int playerLives = constants::ballLiveAmount;

    // Text display on screen
    sf::Font fontVerdana = sf::Font(constants::fontPath);
    sf::Text textState = sf::Text(fontVerdana);
    sf::Text textLives = sf::Text(fontVerdana);

public:
    GameManager(void);
    ~GameManager(void){}

    void reset(void);

    void mainLoopRun(void);
};
//=================================================================================================================

// Function to create an entity objet of type T using args as the constructor arguments
// We use variadic template to pass any number of arguments



#endif // GAME_MANAGER_H
#endif // INC_X15_MAIN_CALL_MENU