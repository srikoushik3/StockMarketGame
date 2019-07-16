#include "GameStateBase.h"
#include "UserManager.h"
#include "StockManager.h"
#include <memory>

using namespace std;

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it assigns a shared pointer of
 *    UserManager type to userManager and a shared pointer of StockManager
 *    type to stockManager.
 */
GameStateBase::GameStateBase()
{
    userManager = make_shared<UserManager>();
    stockManager = make_shared<StockManager>();
}
