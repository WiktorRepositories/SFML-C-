#ifndef INC_CONSTANTS_H
#define INC_CONSTANTS_H

#define WINDOW_WIDTH 520u
#define WINDOW_HEIGHT 450u
#define WINDOW_NAME "Moving paddle"

#define BALL_SPEED 6u

#define PADDLE_WIDTH 60u
#define PADDLE_HEIGHT 20u
#define PADDLE_SPEED 8.0f

#define BRICK_WIDTH 43.0f
#define BRICK_HEIGHT 20.0f
#define BRICK_OFFSET ( BRICK_WIDTH / 2u )
#define BRICKS_COLUMNS 10u
#define BRICKS_ROWS 4u

#define PATH_WINDOW_GAME "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x14_Project_intro_/images/background.jpg"
#define PATH_BALL "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x14_Project_intro_/images/ball.png"
#define PATH_PADDLE "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x14_Project_intro_/images/paddle.png"
#define PATH_BRICK_01 "D:/01_Programistyczne_pliki/xA0_WZ_WorkSpace_for_C++_project/INC/x14_Project_intro_/images/brick01.png"

/***************************************************************************************************************************
 * Code for Breakout game
 * Based on a talk by Vittorio Romero
 * Used the SFML graphic library
 */
namespace constants
{
    // Game window settings
    inline constexpr char windowName[] = WINDOW_NAME;
    inline constexpr unsigned int windowWidth = WINDOW_WIDTH;
    inline constexpr unsigned int windowHeight = WINDOW_HEIGHT;
    inline constexpr char windowTexturePath[] = PATH_WINDOW_GAME;
    
    // Bouncing Ball settings
    inline constexpr int ballSpeed = BALL_SPEED;
    inline constexpr char ballTexturePath[] = PATH_BALL;

    // Moving Paddle settings
    inline constexpr unsigned int paddleWidth = PADDLE_WIDTH;
    inline constexpr unsigned int paddleHeight = PADDLE_HEIGHT;
    inline constexpr float paddleSpeed = PADDLE_SPEED;
    inline constexpr char paddleTexturePath[] = PATH_PADDLE;

    // Game objects Bricks settings
    inline constexpr float brickWidth = BRICK_WIDTH;
    inline constexpr float brickHeight = BRICK_HEIGHT;
    inline constexpr float birckOffset = BRICK_OFFSET;
    inline constexpr unsigned int bricksColumns = BRICKS_COLUMNS;
    inline constexpr unsigned int bricksRows = BRICKS_ROWS;
    inline constexpr unsigned int bricksAmount = bricksColumns * bricksRows;
    inline constexpr char brickTexturePath[] = PATH_BRICK_01;
};
//=========================================================================================================================

#endif // INC_CONSTANTS_H