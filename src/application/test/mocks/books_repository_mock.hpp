#ifndef BOOKS_REPOSITORY_MOCK__HPP__
#define BOOKS_REPOSITORY_MOCK__HPP__

#include <application/ports/repositories/books_repository_port.hpp>

class BooksRepositoryMock : public BooksRepositoryPort
{
public:

    static std::unique_ptr<BooksRepositoryMock> make()
    {
        return std::unique_ptr<BooksRepositoryMock>(
            new BooksRepositoryMock());
    }

    BookDTO create_in;
    BookDTO create_out;
    virtual BookDTO create(const BookDTO & _book)
    {
        create_in = _book;
        return create_out;
    }

    std::string exists_in;
    bool exists_out;
    virtual bool exists(const std::string & _isbn)
    {
        exists_in = _isbn;
        return exists_out;
    }
};

#endif
