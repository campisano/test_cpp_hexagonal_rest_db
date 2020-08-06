#include "testutils.hpp"

#include "domain/author.hpp"

TEST_GROUP(AuthorTG) {};

TEST(AuthorTG, when_create_new_then_new_returns)
{
    Author a("name");
}

TEST(AuthorTG, when_create_empty_name_then_throw_exception)
{
    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "Name '' is invalid", Author(""));
}

TEST(AuthorTG, when_get_name_then_name_returns)
{
    Author a("name");

    CHECK_EQUAL(std::string("name"), a.name());
}

TEST(AuthorTG, when_set_notempty_name_then_set)
{
    Author a("name");

    a.name("new_name");

    CHECK_EQUAL(std::string("new_name"), a.name());
}


TEST(AuthorTG, when_set_empty_name_then_throw_exception)
{
    Author a("name");

    CHECK_THROWS_STDEXCEPT(
        std::runtime_error, "Name '' is invalid", a.name(""));
}
