#include "doctest.h"

#include <stdexcept>
#include "domain/author.hpp"

TEST_SUITE_BEGIN("AuthorTG");

TEST_CASE("when_create_new_then_new_returns")
{
    Author a("name");
}

TEST_CASE("when_create_empty_name_then_throw_exception")
{
    CHECK_THROWS_WITH_AS(Author(""), "Name '' is invalid", std::runtime_error);
}

TEST_CASE("when_get_name_then_name_returns")
{
    Author a("name");

    CHECK_EQ(std::string("name"), a.name());
}

TEST_CASE("when_set_notempty_name_then_set")
{
    Author a("name");

    a.name("new_name");

    CHECK_EQ(std::string("new_name"), a.name());
}


TEST_CASE("when_set_empty_name_then_throw_exception")
{
    Author a("name");

    CHECK_THROWS_WITH_AS(a.name(""), "Name '' is invalid", std::runtime_error);
}

TEST_SUITE_END();
