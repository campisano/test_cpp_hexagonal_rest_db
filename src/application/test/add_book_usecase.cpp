#include "testutils.hpp"

#include <iostream>
#include <memory>

#include <application/exceptions/book_already_exists_exception.hpp>
#include <application/exceptions/book_invalid_exception.hpp>
#include "../src/usecases/add_book_usecase.hpp"
#include "mocks/authors_repository_mock.hpp"
#include "mocks/books_repository_mock.hpp"

TEST_GROUP(AddBookUsecaseTG) {};

TEST(AddBookUsecaseTG, when_add_new_then_get_authors)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    auto response = usecase.execute(
        {"isbn", "title", {"author1"}, "description"});

    CHECK_EQUAL(std::string("author1"), authors_rep->findByNameIn_in.front());
}

TEST(AddBookUsecaseTG, when_add_new_then_check_exists)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    auto response = usecase.execute(
        {"isbn", "title", {"author1"}, "description"});

    CHECK_EQUAL(std::string("isbn"), books_rep->exists_in);
}

TEST(AddBookUsecaseTG, when_add_new_then_call_create)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    auto response = usecase.execute(
        {"isbn", "title", {"author1"}, "description"});

    CHECK_EQUAL(std::string("isbn"), books_rep->create_in.isbn);
    CHECK_EQUAL(std::string("title"), books_rep->create_in.title);
    CHECK_EQUAL(std::string("author1"), books_rep->create_in.authors.front());
    CHECK_EQUAL(std::string("description"), books_rep->create_in.description);
}

TEST(AddBookUsecaseTG, when_add_new_then_new_returns)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    books_rep->create_out = {"isbn", "title", {"author1"}, "description"};
    AddBookUsecase usecase(*books_rep, *authors_rep);

    auto response = usecase.execute(
        {"isbn", "title", {"author1"}, "description"});

    CHECK_EQUAL(std::string("isbn"), response.isbn);
    CHECK_EQUAL(std::string("title"), response.title);
    CHECK_EQUAL(std::string("author1"), response.authors.front());
    CHECK_EQUAL(std::string("description"), response.description);
}

TEST(AddBookUsecaseTG, when_add_existent_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = true;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    CHECK_THROWS_STDEXCEPT(
        BookAlreadyExistsException,
        "Book with isbn 'isbn' already exists", usecase.execute(
            {"isbn", "title", {"author1"}, "description"}));
}

TEST(AddBookUsecaseTG, when_add_empty_isbn_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    CHECK_THROWS_STDEXCEPT(
        BookInvalidException,
        "Isbn '' is invalid", usecase.execute(
            {"", "title", {"author1"}, "description"}));
}

TEST(AddBookUsecaseTG, when_add_invalid_title_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = { {"author1"} };
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    CHECK_THROWS_STDEXCEPT(
        BookInvalidException,
        "Title '' is invalid", usecase.execute(
            {"isbn", "", {"author1"}, "description"}));
}

TEST(AddBookUsecaseTG, when_add_invalid_author_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = {};
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    CHECK_THROWS_STDEXCEPT(
        BookInvalidException,
        "Book authors are invalid, expected 1 or more authors, requested 0",
        usecase.execute(
            {"isbn", "title", {}, "description"}));
}

TEST(AddBookUsecaseTG, when_add_unexistent_author_then_throw_exception)
{
    auto authors_rep = AuthorsRepositoryMock::make();
    authors_rep->findByNameIn_out = {};
    auto books_rep = BooksRepositoryMock::make();
    books_rep->exists_out = false;
    AddBookUsecase usecase(*books_rep, *authors_rep);

    CHECK_THROWS_STDEXCEPT(
        BookInvalidException,
        "Book authors are invalid, authors requested 1, authors found 0",
        usecase.execute(
            {"isbn", "title", { "author1" }, "description"}));
}
