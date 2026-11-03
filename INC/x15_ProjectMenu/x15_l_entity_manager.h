#include "gamelib/_include_definitions.h"
#ifdef INC_ENTITY_MANAGER_H

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

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
    RUNNING
};
//=========================================================================================================================

sf::Texture TextureCreator(const char* path, const char* errorMessage);

bool DetectRisingEdge(bool input, bool& laststate);
bool DetectFallingEdge(bool input, bool& laststate);

//=================================================================================================================

// Function to create an entity objet of type T using args as the constructor arguments
// We use variadic template to pass any number of arguments
template <typename T, typename... ARGS>
T& Create(ARGS&&... args)
{
    static_assert(std::is_base_of<Entity, T>::value, "T type papameter in Create() must be derived from Entity");

    // Create a unique ptr to the Entity
    // Forward the arguments to the Entity constructor
    auto upEntity = std::make_unique<T>(std::forward<ARGS>(args)...);

    // Make an alias pointer to the allocated memory This will be stored in the Entity type vector
    auto upAlias = upEntity.get();

    // Get the has code for the Entity object type
    auto hashCode = typeid(T).hash_code();

    
}


#endif // ENTITY_MANAGER_H
#endif // INC_ENTITY_MANAGER_H