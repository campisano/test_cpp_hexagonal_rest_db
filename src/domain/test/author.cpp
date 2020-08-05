#include "testutils.hpp"

#include "domain/author.hpp"

TEST_GROUP(AuthorTG) {};

TEST(AuthorTG, creation_with_notempty_name)
{
    Author a("name");
}

TEST(AuthorTG, creation_with_empty_name)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "Name '' is invalid", Author(""));
}

TEST(AuthorTG, author_get_name)
{
    Author a("name");

    CHECK_EQUAL(std::string("name"), a.name());
}

TEST(AuthorTG, author_set_notempty_name)
{
    Author a("name");

    a.name("new_name");

    CHECK_EQUAL(std::string("new_name"), a.name());
}


TEST(AuthorTG, author_set_empty_name)
{
    Author a("name");

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "Name '' is invalid", a.name(""));
}
