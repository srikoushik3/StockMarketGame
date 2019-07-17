#include "NewGameState.h"
#include <memory>

using namespace std;
using json = nlohmann::json;

/* 
 * Parameters   : Shared pointer to GameStateManager
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it calls the Decorator constructor by
 *    passing in shared pointer to GameStateManager, via MIL, since
 *    NewGameState inherits from the Decorator class.
 */
NewGameState::NewGameState(shared_ptr<GameStateManager> gsm): Decorator(gsm) {}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it takes in a JSON file and calls the
 *    loadStocksFromFile under stockManager, by passing this JSON as parameter,
 *    to read in stocks from the JSON.
 */
void NewGameState::createStocksFromFile(json & stocks) {
    this->stockManager->loadStocksFromFile(stocks);
}

void NewGameState::initalizeGame(json & stocks, vector<string> usernames){
    this->createStocksFromFile(stocks);
    float avgSharePrice = this->stockManager->getAvgSharePrice();
    this->createUsers(usernames, avgSharePrice);
}

/* 
 * Parameters   : Vector of strings
 * Return Value : None
 * Description  : 
 *    When this method is invoked it takes in a vector of usernames and calls the
 *    createUsersFromUsername under userManager, by passing this vector as parameter,
 *    to read in user from the vector.
 */
void NewGameState::createUsers(vector<string> usernames, float avgSharePrice){
    this->userManager->createUsersFromUsername(usernames, avgSharePrice);
}
