#ifndef APPLICATION_FACTORY__HPP__
#define APPLICATION_FACTORY__HPP__

#include <memory>

#include <application/ports/usecases/add_author_usecase_port.hpp>
#include <application/ports/usecases/add_book_usecase_port.hpp>
#include <application/ports/repositories/authors_repository_port.hpp>
#include <application/ports/repositories/books_repository_port.hpp>

class ApplicationFactory
{
private:
    explicit ApplicationFactory();

public:
    static std::unique_ptr<AddAuthorUsecasePort> makeAddAuthorUsecase(
        AuthorsRepositoryPort & _repository);

    static std::unique_ptr<AddBookUsecasePort> makeAddBookUsecase(
        BooksRepositoryPort & _books_repository,
        AuthorsRepositoryPort & _authors_repository);
};

#endif
