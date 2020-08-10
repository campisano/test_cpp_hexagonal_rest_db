#ifndef BOOKS_REPOSITORY_PORT__HPP__
#define BOOKS_REPOSITORY_PORT__HPP__

#include <list>
#include <memory>
#include <string>

#include <application/dtos/book_dto.hpp>

class BooksRepositoryPort
{
public:
    virtual ~BooksRepositoryPort() = default;

public:
    virtual BookDTO create(const BookDTO & _book) = 0;
    virtual bool exists(const std::string & _isbn) = 0;

    //TODO
    // List<BookDTO> findAll();
    // Optional<BookDTO> findByIsbn(String isbn);
};

#endif
