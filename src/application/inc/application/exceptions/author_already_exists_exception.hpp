#ifndef AUTHOR_ALREADY_EXISTS_EXCEPTION__HPP__
#define AUTHOR_ALREADY_EXISTS_EXCEPTION__HPP__

#include <stdexcept>
#include <string>

class AuthorAlreadyExistsException : public std::runtime_error
{
public:
    virtual ~AuthorAlreadyExistsException() = default;

public:
    explicit AuthorAlreadyExistsException(const std::string & _message)
        : std::runtime_error(_message)
    {
    }
};

#endif
