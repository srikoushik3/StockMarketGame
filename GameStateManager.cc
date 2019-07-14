#include "GameStateManager.h"

GameStateManager::GameStateManager(){}
GameStateManager::GameStateManager(std::shared_ptr<GameStateManager> gsm): stockManager{gsm->stockManager}, userManager{gsm->userManager} {}
GameStateManager::~GameStateManager(){}
