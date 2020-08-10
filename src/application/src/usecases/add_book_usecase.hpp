#ifndef ADD_BOOK_USECASE__HPP__
#define ADD_BOOK_USECASE__HPP__

#include <application/dtos/book_dto.hpp>
#include <application/ports/usecases/add_book_usecase_port.hpp>
#include <application/ports/repositories/authors_repository_port.hpp>
#include <application/ports/repositories/books_repository_port.hpp>
#include <domain/book.hpp>

class AddBookUsecase : public AddBookUsecasePort
{
public:
    explicit AddBookUsecase(
        BooksRepositoryPort & _books_repository,
        AuthorsRepositoryPort & _authors_repository);
    AddBookUsecase(const AddBookUsecase &) = delete;
    AddBookUsecase(AddBookUsecase &&) = default;
    virtual ~AddBookUsecase();

    AddBookUsecase & operator=(const AddBookUsecase &) = delete;
    AddBookUsecase & operator=(AddBookUsecase &&) = default;

public:
    virtual BookDTO execute(const BookDTO & _book);

private:
    BooksRepositoryPort & m_books_repository;
    AuthorsRepositoryPort & m_authors_repository;
};

#endif
