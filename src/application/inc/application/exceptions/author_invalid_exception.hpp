#ifndef AUTHOR_INVALID_EXCEPTION__HPP__
#define AUTHOR_INVALID_EXCEPTION__HPP__

#include <stdexcept>
#include <string>

class AuthorInvalidException : public std::runtime_error
{
public:
    explicit AuthorInvalidException(const std::string & _message)
        : std::runtime_error(_message)
    {
    }
};

#endif
