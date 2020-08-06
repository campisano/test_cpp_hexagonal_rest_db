#include "testutils.hpp"

#include <iostream>
#include <memory>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>
#include "../src/usecases/add_author_usecase.hpp"

namespace
{
    class RepoMock : public AuthorsRepositoryPort
    {
    public:
        AuthorDTO create_in;
        AuthorDTO create_out;
        virtual AuthorDTO create(const AuthorDTO & _author)
        {
            create_in = _author;
            return create_out;
        }

        std::string exists_in;
        bool exists_out;
        virtual bool exists(const std::string & _name)
        {
            exists_in = _name;
            return exists_out;
        }

        std::string findByName_in;
        std::unique_ptr<AuthorDTO> findByName_out;
	virtual std::unique_ptr<AuthorDTO> findByName(
            const std::string & _name)
        {
            findByName_in = _name;
            return std::move(findByName_out);
        }

        std::list<std::string> findByNameIn_in;
        std::list<AuthorDTO> findByNameIn_out;
	virtual std::list<AuthorDTO> findByNameIn(
            const std::list<std::string> & _author_names)
        {
            findByNameIn_in = _author_names;
            return findByNameIn_out;
        }
    };

    std::unique_ptr<RepoMock> makeRepo()
    {
        return std::unique_ptr<RepoMock>(new RepoMock());
    }
}

TEST_GROUP(AddAuthorUsecaseTG) {};

TEST(AddAuthorUsecaseTG, when_add_new_then_check_exists)
{
    auto repo = makeRepo();
    repo->exists_out = false;
    repo->create_out = {"aaa"};
    AddAuthorUsecase usecase(*repo);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), repo->exists_in)
}

TEST(AddAuthorUsecaseTG, when_add_new_then_call_create)
{
    auto repo = makeRepo();
    repo->exists_out = false;
    repo->create_out = {"aaa"};
    AddAuthorUsecase usecase(*repo);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), repo->create_in.name);
}

TEST(AddAuthorUsecaseTG, when_add_new_then_new_returns)
{
    auto repo = makeRepo();
    repo->exists_out = false;
    repo->create_out = {"aaa"};
    AddAuthorUsecase usecase(*repo);

    auto response = usecase.execute({"aaa"});

    CHECK_EQUAL(std::string("aaa"), response.name);
}

TEST(AddAuthorUsecaseTG, when_add_existent_then_throw_exception)
{
    auto repo = makeRepo();
    repo->exists_out = true;
    AddAuthorUsecase usecase(*repo);

    CHECK_THROWS_STDEXCEPT(
        AuthorAlreadyExistsException,
        "Author with name 'aaa' already exists", usecase.execute({"aaa"}));
}

TEST(AddAuthorUsecaseTG, when_add_empty_name_then_throw_exception)
{
    auto repo = makeRepo();
    repo->exists_out = true;
    AddAuthorUsecase usecase(*repo);

    CHECK_THROWS_STDEXCEPT(
        AuthorInvalidException,
        "Name '' is invalid", usecase.execute({""}));
}
