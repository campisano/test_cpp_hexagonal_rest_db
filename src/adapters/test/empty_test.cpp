#include "CppUTest/TestHarness.h"

TEST_GROUP(EmptyTestTG) {};

TEST(EmptyTestTG, empty)
{
    CHECK_EQUAL(0, 0);
}
