#include "doctest.h"

#include <iostream>
#include <memory>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>
#include "../src/usecases/add_author_usecase.hpp"
#include "mocks/authors_repository_mock.hpp"

TEST_SUITE_BEGIN("AddAuthorUsecaseTG");

TEST_CASE("when_add_new_then_check_exists")
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQ(std::string("aaa"), authors_rep->exists_in);
}

TEST_CASE("when_add_new_then_call_create")
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQ(std::string("aaa"), authors_rep->create_in.name);
}

TEST_CASE("when_add_new_then_new_returns")
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = false;
    authors_rep->create_out = {"aaa"};
    AddAuthorUsecase usecase(*authors_rep);

    auto response = usecase.execute({"aaa"});

    CHECK_EQ(std::string("aaa"), response.name);
}

TEST_CASE("when_add_existent_then_throw_exception")
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = true;
    AddAuthorUsecase usecase(*authors_rep);

    CHECK_THROWS_WITH_AS(usecase.execute({"aaa"}), "Author with name 'aaa' already exists", AuthorAlreadyExistsException);
}

TEST_CASE("when_add_empty_name_then_throw_exception")
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->exists_out = true;
    AddAuthorUsecase usecase(*authors_rep);

    CHECK_THROWS_WITH_AS(usecase.execute({""}), "Name '' is invalid", AuthorInvalidException);
}

TEST_SUITE_END();
