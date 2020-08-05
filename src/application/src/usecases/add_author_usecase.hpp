#ifndef ADD_AUTHOR_USECASE__HPP__
#define ADD_AUTHOR_USECASE__HPP__

#include <application/dtos/author_dto.hpp>
#include <application/ports/usecases/add_author_usecase_port.hpp>
#include <application/ports/repositories/authors_repository_port.hpp>
#include <domain/author.hpp>

class AddAuthorUsecase : public AddAuthorUsecasePort
{
public:
    explicit AddAuthorUsecase(AuthorsRepositoryPort & _authors_repository);
    AddAuthorUsecase(const AddAuthorUsecase &) = delete;
    AddAuthorUsecase(AddAuthorUsecase &&) = default;
    virtual ~AddAuthorUsecase();

    AddAuthorUsecase & operator=(const AddAuthorUsecase &) = delete;
    AddAuthorUsecase & operator=(AddAuthorUsecase &&) = default;

public:
    virtual AuthorDTO execute(const AuthorDTO & _author);

private:
    AuthorsRepositoryPort & m_authors_repository;
};

#endif
