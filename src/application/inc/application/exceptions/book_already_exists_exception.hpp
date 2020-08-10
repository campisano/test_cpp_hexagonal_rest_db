#ifndef BOOK_ALREADY_EXISTS_EXCEPTION__HPP__
#define BOOK_ALREADY_EXISTS_EXCEPTION__HPP__

#include <stdexcept>
#include <string>

class BookAlreadyExistsException : public std::runtime_error
{
public:
    virtual ~BookAlreadyExistsException() = default;

public:
    explicit BookAlreadyExistsException(const std::string & _message)
        : std::runtime_error(_message)
    {
    }
};

#endif
