#include <string>
#include "Exception.h"

using namespace std;

/* 
 * Parameters   : None
 * Return Value : constant pointer to char
 * Description  : 
 *    Since we want the exception to throw a string that explains the
 *    cause of the exception, when this method is invoked it will simply
 *    return the private string str.
 */
const char* StockException::what() {
    return str;
}

/* 
 * Parameters   : None
 * Return Value : constant pointer to char
 * Description  : 
 *    Since we want the exception to throw a string that explains the
 *    cause of the exception, when this method is invoked it will simply
 *    return the private string str.
 */
const char* UserException::what() {
    return str;
}

/* 
 * Parameters   : None
 * Return Value : constant pointer to char
 * Description  : 
 *    Since we want the exception to throw a string that explains the
 *    cause of the exception, when this method is invoked it will simply
 *    return the private string str.
 */
const char* FileIOException::what() {
    return str;
}