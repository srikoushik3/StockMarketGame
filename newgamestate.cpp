#include "newgamestate.h"
#include <memory>

using namespace std;
using json = nlohmann::json;

NewGameState::NewGameState(shared_ptr<GameStateManager> gsm): Decorator(gsm) {}

void NewGameState::createStocksFromFile(json & stocks) {
    this->stockManager->loadStocksFromFile(stocks);
}

void NewGameState::createUsers(vector<string> usernames){
    this->userManager->createUsersFromUsername(usernames);
}
