#include "GameStateManager.h"

GameStateManager::GameStateManager(){}

/* 
 * Parameters   : Shared pointer to GameStateManager
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it takes in gsm, a shared pointer to
 *  ``GameStateManager and assigns stockManager the stockManager gsm points to;
 *    likewise assigns userManager the userManager gsm points to, via MIL.
 */
GameStateManager::GameStateManager(std::shared_ptr<GameStateManager> gsm): stockManager{gsm->stockManager}, userManager{gsm->userManager} {}

GameStateManager::~GameStateManager(){}
