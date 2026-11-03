#include "x15_k_game_manager.h"
#ifdef INC_GAME_MANAGER_H

#define ERROR_DEFAULT_TEXTURE "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x15_ProjectMenu/images/error_default.jpg"
#define ERROR_DEAFULT_FONT "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x15_ProjectMenu/images/verdana.ttf"

/****************************************************************************************************
 * @name    sf::Texture TextureCreator
 * @brief   Creator function for sf::Texture class initialization
 */
sf::Texture TextureCreator(const char* path, const char* errorMessage)
{
    sf::Texture texture;
    if( texture.loadFromFile(path) )
        return texture;
    else
        std::cout << errorMessage << " " << path << std::endl;

    // constexpr char path[] Texture loadinf error, then load ERROR DEFAULT  
    if( !texture.loadFromFile(ERROR_DEFAULT_TEXTURE) ) // Posible ERROR durin loading ERROR_DEFAULT_TEXTURE, need letter changes
        std::cout << "ERROR: Default immage loading fail! " << " error_default.jpg " <<  std::endl;
    return texture;
}
//===================================================================================================

/****************************************************************************************************
 * @name    sf::Font    FontCreator
 * @brief   Creator function for sf::Font class initialization
 */
sf::Font FontCreator(const char* path, const char* errorMessage)
{
    try
    {
        return sf::Font(path);
    }
    catch(const std::exception& e)
    {
        std::cout << errorMessage << " " << path << std::endl;
        std::cerr << e.what() << '\n';
    }
    return sf::Font(ERROR_DEAFULT_FONT);
}
//===================================================================================================

/****************************************************************************************************
 * @name    bool DetectRisingEdge
 * @brief   Detect change on the imput from FALSE to TRUE
 */
bool DetectRisingEdge(bool currstate, bool& laststate)
{
    bool retval = false;
    if(currstate)
    {
        if(!laststate) retval = true;
    }
    laststate = currstate;
    return retval;
}
//===================================================================================================

/****************************************************************************************************
 * @name    bool DetectFallingEdge
 * @brief   Detect change on the imput from TRUE to FALSE
 */
bool DetectFallingEdge(bool currstate, bool& laststate)
{
    bool retval = false;
    if(laststate)
    {
        if(!currstate) retval = true;
    }
    laststate = currstate;
    return retval;
}
//===================================================================================================

/****************************************************************************************************
 * @name    GameManager::GameManager
 * @brief   Game initialization
 */
GameManager::GameManager(void)
{
    vecBricks.reserve(constants::bricksColumns * constants::bricksRows);
    reset();
    gameWindow.setFramerateLimit(10);

    float positionX = constants::windowWidth / 2.0 - 100.0;
    float positionY = constants::windowHeight / 2.0 - 100.0;

    textState.setPosition( sf::Vector2f( positionX, positionY ));
    textState.setCharacterSize(35);
    textState.setFillColor(sf::Color::White);
    textState.setString("PAUSED");

    positionX = (constants::windowWidth / 2.0) - 65.0;
    positionY = (constants::windowHeight / 2.0) - 50.0; 

    textLives.setPosition(sf::Vector2f( positionX, positionY ));
    textLives.setCharacterSize(35);
    textLives.setFillColor(sf::Color::White);
    textLives.setString("Lives: " + std::to_string(playerLives));

    gameWindow.draw(textState);
    gameWindow.draw(textLives);
}
//===================================================================================================

/****************************************************************************************************
 * @name    GameManager::reset
 * @brief   Reinitialization of a game
 */
void GameManager::reset(void)
{
    for(unsigned int i=0; i<constants::bricksColumns; ++i)
    {
        for(unsigned int j=0; j<constants::bricksRows; ++j)
        {
            // Calculate the brick's position
            float x = constants::birckOffset + (i + 1)*constants::brickWidth;
            float y = (j + 1)*constants::brickHeight;
            // Create the brick object
            vecBricks.emplace_back(x, y, &textureBrick);
        }
    }
    ball.setPosition(constants::windowWidth/2, constants::windowHeight/2);
    paddle.setPosition(constants::windowWidth/2, constants::windowHeight - constants::paddleHeight);
    paddle.setSpeed(0.0, 0.0);

    enumState = EGameState::PAUSED;
    playerLives = constants::ballLiveAmount;
}
//===================================================================================================

/****************************************************************************************************
 * @name    GameManager::mainLoopRun
 * @brief   Game initialization
 */
void GameManager::mainLoopRun(void)
{
    bool lastStatePause = false;
    bool lastStateReset = false;

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

        // User presed "Esc"
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;

        // User preset "P" this will pause game
        // Rising edge for a P button
        if( DetectRisingEdge( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P), lastStatePause) )
        {
            switch (enumState)
            {
            case EGameState::PAUSED:  enumState = EGameState::RUNNING;
                textState.setString("");
                textLives.setString("LIVES: " + std::to_string(playerLives));
                break;
            case EGameState::RUNNING: enumState = EGameState::PAUSED;
                break;
            default: enumState = EGameState::RUNNING;
                break;
            }
        }

        // Game date will be reinitialized
        if( DetectRisingEdge( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R), lastStateReset) ) 
        {
            enumState = EGameState::PAUSED;
            reset();
        }
            
        // Game is not paused
        if(enumState == EGameState::RUNNING)
        {
            // Calculated the updated graphic
            background.update();
            ball.update();
            paddle.update();

            for(auto& i : vecBricks) i.update();

            HandleColision(ball, paddle);
            // Check every brick for a colision wth ball
            for(auto& i : vecBricks) HandleColision(ball, i);

            // Erase any destroyed bricks from grid
            // Remove if moves all lemets to back for which the conditional is true
            // It returns an iterator to the first moved element
            // We then call erase witch the iterator as argument
            // This will erase every eleent following this iterator
            vecBricks.erase( std::remove_if(std::begin(vecBricks), std::end(vecBricks), 
                            [](const Brick& refbrick) { return refbrick.isDestroyed(); } ), 
                            std::end(vecBricks) );

            if(ball.isDestroyed())
            {
                --playerLives;
                enumState = EGameState::PAUSED;
                ball.setPosition(constants::windowWidth/2.0, constants::windowHeight/2.0);
            }
            if(vecBricks.empty())
            {
                enumState = EGameState::PLAYER_WINS;
            }          
            if(playerLives <= 0) 
            {
                enumState = EGameState::GAME_OVER;
            }
        }
        else
        {
            switch (enumState)
            {
            case EGameState::PAUSED:
                textState.setString("PAUSED, P to run");
                textLives.setString("LIVES: " + std::to_string(playerLives));
                break;

            case EGameState::GAME_OVER:
                textState.setString("GAME OVER, R to restart");
                textLives.setString("LIVES: " + std::to_string(playerLives));
                break;

            case EGameState::PLAYER_WINS:
                textState.setString("PLAYER WINS, R to restart");
                textLives.setString("LIVES: " + std::to_string(playerLives));
                break;
            
            default:
                textState.setString("GAME OVER, R to restart");
                textLives.setString("LIVES: " + std::to_string(playerLives));
                enumState = EGameState::PAUSED;
                break;
            }
        }

        // Display the updaed graphic
        background.draw(gameWindow);
        ball.draw(gameWindow);
        paddle.draw(gameWindow);

        for(auto& i : vecBricks) i.draw(gameWindow);

        // Display the updated graphic
        gameWindow.draw(textState);
        gameWindow.draw(textLives);
        gameWindow.display();
    }
    gameWindow.close();
}
//===================================================================================================

#endif // INC_X15_MAIN_CALL_MENU