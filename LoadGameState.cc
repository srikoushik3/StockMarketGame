#include <string>
#include <fstream>
#include "LoadGameState.h"
#include "StockManager.h"
#include "UserManager.h"
#include "json.hpp"
#include "Exception.h"

using json = nlohmann::json;
using namespace std;

LoadGameState::LoadGameState(shared_ptr<Decorator> gsm): Decorator(gsm) {}

void LoadGameState::loadStocksFromFile(json& stocks) {
    try {
        stockManager->loadStocksFromFile(stocks);
    }
    catch(...){
        // throw Could not load JSON Stocks
        throw FileIOException("Could not load JSON Stocks");
    }
}

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
