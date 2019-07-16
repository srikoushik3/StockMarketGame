#include <string>
#include <fstream>
#include "LoadGameState.h"
#include "StockManager.h"
#include "UserManager.h"
#include "json.hpp"
#include "Exception.h"

using json = nlohmann::json;
using namespace std;

/* 
 * Parameters   : Shared pointer to GameStateManager
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it calls the constructor for Decorator
 *    by passing in a shared pointer to GameStateManager, via MIL, since
 *    LoadGameState inherits from the Decorator class.
 */
LoadGameState::LoadGameState(shared_ptr<GameStateManager> gsm): Decorator(gsm) {}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the loadStocksFromFile method
 *    defined under stockManager to load all the stock information from
 *    previous game session. If error occurs, then exception is thrown.
 */
void LoadGameState::loadStocksFromFile(json& stocks) {
    try {
        stockManager->loadStocksFromFile(stocks);
    }
    catch(...){
        // throw Could not load JSON Stocks
        throw FileIOException("Could not load JSON Stocks");
    }
}

/* 
 * Parameters   : Reference to JSON
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the loadUsersFromFile method
 *    defined under userManager to load all the user information from
 *    previous game session. If error occurs, then exception is thrown.
 */
void LoadGameState::loadUsersFromFile(json& users) {
    try {
        userManager->loadUsersFromFile(users);
    }
    catch(...){
        // throw Could not load JSON Users
        throw FileIOException("Could not load JSON Users");
    }
}

LoadGameState::~LoadGameState(){}
