#ifndef BOOK_INVALID_EXCEPTION__HPP__
#define BOOK_INVALID_EXCEPTION__HPP__

#include <stdexcept>
#include <string>

class BookInvalidException : public std::runtime_error
{
public:
    virtual ~BookInvalidException() = default;

public:
    explicit BookInvalidException(const std::string & _message)
        : std::runtime_error(_message)
    {
    }
};

#endif
