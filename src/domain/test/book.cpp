#include "doctest.h"

#include <stdexcept>
#include "domain/book.hpp"

namespace
{
    std::list<Author> makeAuthors();
}

TEST_SUITE_BEGIN("BookTG");

TEST_CASE("when_create_with_empty_description_then_create")
{
    auto authors = makeAuthors();

    Book b("isbn", "title", authors, "");
}

TEST_CASE("when_create_with_empty_isbn_then_throw_exception")
{
    auto authors = makeAuthors();

    CHECK_THROWS_WITH_AS(Book("", "title", authors, ""), "Isbn '' is invalid", std::runtime_error);
}

TEST_CASE("when_create_with_empty_title_then_create")
{
    auto authors = makeAuthors();

    CHECK_THROWS_WITH_AS(Book("isbn", "", authors, ""), "Title '' is invalid", std::runtime_error);
}

TEST_CASE("when_create_with_empty_authors_then_throw_exception")
{
    std::list<Author> authors;

    CHECK_THROWS_WITH_AS(Book("isbn", "title", authors, ""), "Book authors are invalid, expected 1 or more authors, requested 0", std::runtime_error);
}

TEST_CASE("when_get_isbn_then_isbn_returns")
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQ(std::string("isbn"), b.isbn());
}

TEST_CASE("when_get_title_then_title_returns")
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQ(std::string("title"), b.title());
}

TEST_CASE("when_get_authors_then_authors_returns")
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQ(1, b.authors().size());
    CHECK_EQ(std::string("author"), b.authors().front()->name());
}

TEST_CASE("when_get_description_then_description_returns")
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQ(std::string("description"), b.description());
}

namespace
{
    std::list<Author> makeAuthors()
    {
        std::list<Author> authors;
        authors.push_back(Author("author"));
        return authors;
    }
}

TEST_SUITE_END();
