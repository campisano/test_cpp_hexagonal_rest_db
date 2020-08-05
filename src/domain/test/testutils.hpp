#ifndef TESTUTILS__HPP__
#define TESTUTILS__HPP__

#include <string>
#include "CppUTest/TestHarness.h"

#if CPPUTEST_USE_STD_CPP_LIB
#define CHECK_THROWS_STDEXCEPT(expected, message, expression) \
    { \
    SimpleString failure_msg("expected to throw "#expected "\nbut threw nothing"); \
    bool caught_expected = false; \
    try { \
        (expression); \
    } catch(const expected & _exc) { \
        if(std::string(message).compare(_exc.what()) == 0) { \
            caught_expected = true; \
        } else { \
            failure_msg = SimpleString("expected to throw message '") + message + "'\nbut threw '" + _exc.what() + "'"; \
        } \
    } catch(...) { \
        failure_msg = "expected to throw " #expected "\nbut threw a different type"; \
    } \
    if (!caught_expected) { \
        UtestShell::getCurrent()->fail(failure_msg.asCharString(), __FILE__, __LINE__); \
    } \
    else { \
        UtestShell::getCurrent()->countCheck(); \
    } \
    }
#endif /* CPPUTEST_USE_STD_CPP_LIB */

#endif
