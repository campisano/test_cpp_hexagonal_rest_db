#include <application/application_factory.hpp>

#include "usecases/add_author_usecase.hpp"
#include "usecases/add_book_usecase.hpp"

ApplicationFactory::ApplicationFactory()
{
}

std::unique_ptr<AddAuthorUsecasePort>
ApplicationFactory::makeAddAuthorUsecase(
    AuthorsRepositoryPort & _repository)
{
    return std::unique_ptr<AddAuthorUsecasePort>(
        new AddAuthorUsecase(_repository));
}

std::unique_ptr<AddBookUsecasePort>
ApplicationFactory::makeAddBookUsecase(
    BooksRepositoryPort & _books_repository,
    AuthorsRepositoryPort & _authors_repository)
{
    return std::unique_ptr<AddBookUsecasePort>(
        new AddBookUsecase(_books_repository, _authors_repository));
}
