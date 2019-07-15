#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <string>
#include <exception>

// Declare the StockException Class
class StockException : public std::exception {
    const char* str;
  public:
    // 
    StockException(const char* msg) : str{msg} {}
    // Implement the pure virtual function e.what() from standard exception
    const char* what();
    ~StockException(){}
};

// Declare the UserException Class
class UserException : public std::exception {
    const char* str;
  public:
    UserException(const char* msg) : str{msg} {}
    // Implement the pure virtual function e.what() from standard exception
    const char* what();
    ~UserException(){}
};

// Declare the FileIOException Class
class FileIOException : public std::exception {
    const char* str;
  public:
    FileIOException(const char* msg) : str{msg} {}
    // Implement the pure virtual function e.what() from standard exception
    const char* what();
    ~FileIOException(){}
};

#endif