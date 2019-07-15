#include <string>
#include "Exception.h"

using namespace std;

// Define e.what() in the StockException Class by returning private string
const char* StockException::what() {
    return str;
}

// Define e.what() in the UserException Class by returning private string
const char* UserException::what() {
    return str;
}

// Define e.what() in the FileIOException Class by returning private string
const char* FileIOException::what() {
    return str;
}