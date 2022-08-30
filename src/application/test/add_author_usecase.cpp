#include "testutils.hpp"

#include <iostream>
#include <memory>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>
#include "../src/usecases/add_author_usecase.hpp"
#include "mocks/authors_repository_mock.hpp"

TEST_GROUP(AddAuthorUsecaseTG) {};

TEST(AddAuthorUsecaseTG, when_add_new_then_check_exists)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), authors_rep->exists_in);
}

TEST(AddAuthorUsecaseTG, when_add_new_then_call_create)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), authors_rep->create_in.name);
}

TEST(AddAuthorUsecaseTG, when_add_new_then_new_returns)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), response.name);
}

TEST(AddAuthorUsecaseTG, when_add_existent_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = true;
    AddAuthorUsecase usecase(*authors_rep);

    CHECK_THROWS_STDEXCEPT(
        AuthorAlreadyExistsException,
        "Author with name 'aaa' already exists", usecase.execute({"aaa"}));
}

TEST(AddAuthorUsecaseTG, when_add_empty_name_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = true;
    AddAuthorUsecase usecase(*authors_rep);

    CHECK_THROWS_STDEXCEPT(
        AuthorInvalidException,
        "Name '' is invalid", usecase.execute({""}));
}
