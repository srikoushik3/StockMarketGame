#include "Decorator.h"
#include <memory>

using namespace std;

/* 
 * Parameters   : shared pointer to GameStateManager
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns value to the shared pointer
 *    and calls the GameStateManager constuctor by passing in the shared
 *    pointer to GameStateManager, via MIL.
 */
Decorator::Decorator(shared_ptr<GameStateManager> gsm): gsm(gsm), GameStateManager(gsm){}
