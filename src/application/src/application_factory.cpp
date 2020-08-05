#include <application/application_factory.hpp>

#include "usecases/add_author_usecase.hpp"

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
