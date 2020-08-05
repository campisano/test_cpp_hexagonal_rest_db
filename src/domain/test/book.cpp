#include "testutils.hpp"

#include "domain/book.hpp"

namespace
{
    std::vector<std::unique_ptr<Author>> makeAuthors();
}

TEST_GROUP(BookTG) {};

TEST(BookTG, creation_with_empty_description)
{
    auto authors = makeAuthors();

    Book b("a", "b", authors, "");
}

TEST(BookTG, creation_with_empty_isbn)
{
    auto authors = makeAuthors();

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Isbn '' is invalid", Book("", "b", authors, ""));
}

TEST(BookTG, creation_with_empty_title)
{
    auto authors = makeAuthors();

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Title '' is invalid", Book("a", "", authors, ""));
}

TEST(BookTG, creation_with_empty_authors)
{
    std::vector<std::unique_ptr<Author>> authors;

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error,
        "Book authors are invalid, expected 1 or more authors, requested 0",
        Book("a", "b", authors, ""));
}

TEST(BookTG, author_get_isbn)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("isbn"), b.isbn());
}

TEST(BookTG, author_get_title)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("title"), b.title());
}

TEST(BookTG, author_get_authors)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(1, b.authors().size());
    CHECK_EQUAL(std::string("a"), b.authors().front()->name());
}

TEST(BookTG, author_get_description)
{
    auto authors = makeAuthors();
    Book b("isbn", "title", authors, "description");

    CHECK_EQUAL(std::string("description"), b.description());
}

namespace
{
    std::vector<std::unique_ptr<Author>> makeAuthors()
    {
        std::vector<std::unique_ptr<Author>> authors;
        std::unique_ptr<Author> a(new Author("a"));
        authors.push_back(std::move(a));
        return authors;
    }
}
