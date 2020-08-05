#ifndef ADD_AUTHOR_USECASE_PORT__HPP__
#define ADD_AUTHOR_USECASE_PORT__HPP__

#include <application/dtos/author_dto.hpp>

class AddAuthorUsecasePort
{
public:
    virtual ~AddAuthorUsecasePort() = default;
    virtual AuthorDTO execute(const AuthorDTO & _author) = 0;
};

#endif
