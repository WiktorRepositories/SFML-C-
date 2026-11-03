#include "_include_definitions.h"
#ifdef INC_OBJECTS_HANDLERS_H

#include "ball_enthetity.h"
#include "paddle_enthentity.h"
#include "brick_enthity.h"

// Determine wheather two entities overlap
bool IsInteracting(const Entity& refentA, const Entity& refentB);

// Resolve potential collision between the ball and the paddle
void HandleColision(Ball& refball, const Paddle& refpaddle);

// Resolve potential collision between the ball and a brick
void HandleColision(Ball& refball, Brick& refbrick);
//===============================================================================

#endif // INC_OBJECTS_HANDLERS_H