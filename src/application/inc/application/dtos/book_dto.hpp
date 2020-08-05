#ifndef BOOK_DTO__HPP__
#define BOOK_DTO__HPP__

#include <list>
#include <string>

struct BookDTO
{
    std::string isbn;
    std::string title;
    std::list<std::string> authors;
    std::string description;
};

#endif
