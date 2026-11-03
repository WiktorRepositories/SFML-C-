#include "objects_handlers.h"
#ifdef INC_OBJECTS_HANDLERS_H

#ifndef OBJECTS_HANDLERS_H
#define OBJECTS_HANDLERS_H

#include "x_debug_functions.h"

/*********************************************************************************************************
 * @name IsInteracting
 * @brief Determine wheather two entities overlap
 */
bool IsInteracting(const Entity& refentA, const Entity& refentB)
{
    sf::FloatRect boxA = refentA.getBoundingbox();
    sf::FloatRect boxB = refentB.getBoundingbox();

    // Return values fron findIntersection is : std::optional<sf::FloatRect>
    if(boxA.findIntersection(boxB).has_value()) 
        return true;
    else 
        return false;
}
//========================================================================================================

/*********************************************************************************************************
 * @name HandleColision(Ball& refball, const Paddle& refpaddle)
 * @brief Resolve potential collision between the ball and the paddle
 */
void HandleColision(Ball& refball, const Paddle& refpaddle)
{
    if(IsInteracting(refball, refpaddle))
    {
        refball.moveUp();

        if(refball.x() < refpaddle.x()) 
            refball.moveLeft();
        else 
            refball.moveRight();
    }
}
//========================================================================================================

/*********************************************************************************************************
 * @name HandleColision(Ball& refball, Brick& refbrick)
 * @brief Resolve potential collision between the ball and a brick
 */
void HandleColision(Ball& refball, Brick& refbrick)
{
    if(IsInteracting(refbrick, refball))
    {
        //std::cout << ">> HandleColision: Ball Brick" << std::endl;
        refbrick.weakenByAmount(1);
        if(refbrick.isTopWeak())
            refbrick.destroy();

        // Make the new direction depend on where the colision occurs on the brick
        // If the ball collides on the side of the brick, make the ball bounce
        // If the ball collides on the top, bottom of the brick, makes ball bounce

        // First we find the amount of overlap in each direction
        // The smaller the left overlap, the closer the ball is to the left side of brick
        // And similar for the other sides of the brick
        float overlapLeft = refball.right() - refbrick.left();
        float overlapRight = refbrick.right() - refball.left();
        float overlapTop = refball.bottom() - refbrick.top();
        float overlapBottom = refbrick.bottom() - refball.top();

        // If the left overlap is smaller then the right overlap the ball hit left site
        bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight) ? true : false;
        bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom) ? true : false;

        // Use the right or left overlap as apropriate
        float minOverlap_x = fromLeft ? overlapLeft : overlapRight;
        float minOverlap_y = fromTop ? overlapTop : overlapBottom;

        // If the ball hit the left or right side of the brick, change its horizontal direction
        // If the ball hit the top or bottom of the brick change its vertical direction
        if(std::abs(minOverlap_x) < std::abs(minOverlap_y) )
        {
            if(fromLeft) 
                refball.moveLeft();
            else 
                refball.moveRight();
        }
        else
        {
            if(fromTop) 
                refball.moveUp();
            else 
                refball.moveDown();
        }
    }
}
//====================================================================================

#endif // OBJECTS_HANDLERS_H
#endif // INC_OBJECTS_HANDLERS_H