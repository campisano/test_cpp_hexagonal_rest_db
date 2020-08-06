#include "testutils.hpp"

#include "domain/book.hpp"

namespace
{
    std::list<Author> makeAuthors();
}

TEST_GROUP(BookTG) {};

TEST(BookTG, when_create_with_empty_description_then_create)
{
    auto authors = makeAuthors();

    Book b("isbn", "title", authors, "");
}

TEST(BookTG, when_create_with_empty_isbn_then_throw_exception)
{
    auto authors = makeAuthors();

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Isbn '' is invalid", Book("", "title", authors, ""));
}

TEST(BookTG, when_create_with_empty_title_then_create)
{
    auto authors = makeAuthors();

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Title '' is invalid", Book("isbn", "", authors, ""));
}

TEST(BookTG, when_create_with_empty_authors_then_throw_exception)
{
    std::list<Author> authors;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Book authors are invalid, expected 1 or more authors, requested 0",
        Book("isbn", "title", authors, ""));
}

TEST(BookTG, when_get_isbn_then_isbn_returns)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("isbn"), b.isbn());
}

TEST(BookTG, when_get_title_then_title_returns)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("title"), b.title());
}

TEST(BookTG, when_get_authors_then_authors_returns)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(1, b.authors().size());
    CHECK_EQUAL(std::string("author"), b.authors().front()->name());
}

TEST(BookTG, when_get_description_then_description_returns)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("description"), b.description());
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
