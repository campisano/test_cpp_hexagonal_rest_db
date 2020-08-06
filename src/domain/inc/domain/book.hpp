#ifndef BOOK__HPP__
#define BOOK__HPP__

#include <list>
#include <memory>
#include <string>

#include <domain/author.hpp>

class Book
{
public:
    explicit Book(
        const std::string & _isbn,
        const std::string & _title,
        std::list<Author> & _authors,
        const std::string & _description);
    Book(const Book &) = delete;
    Book(Book &&) = default;
    virtual ~Book();

    Book & operator=(const Book &) = delete;
    Book & operator=(Book &&) = default;

public:
    const std::string & isbn() const;
    const std::string & title() const;
    std::list<const Author *> authors() const;
    const std::string & description() const;

private:
    std::string m_isbn;
    std::string m_title;
    std::list<Author> m_authors;
    std::string m_description;
};

#endif
