#ifndef ADD_BOOK_USECASE_PORT__HPP__
#define ADD_BOOK_USECASE_PORT__HPP__

#include <application/dtos/book_dto.hpp>

class AddBookUsecasePort
{
public:
    virtual ~AddBookUsecasePort() = default;

public:
    virtual BookDTO execute(const BookDTO & _book) = 0;
};

#endif
