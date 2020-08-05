#include <domain/book.hpp>

#include <sstream>
#include <stdexcept>
#include <utility>

namespace {
    void ensureValidForCreation(
        const std::string & _isbn,
        const std::string & _title,
        std::vector<std::unique_ptr<Author>> & _authors,
        const std::string & _description);
}

Book::Book(
    const std::string & _isbn,
    const std::string & _title,
    std::vector<std::unique_ptr<Author>> & _authors,
    const std::string & _description)
{
    ensureValidForCreation(_isbn, _title, _authors, _description);
    m_isbn = _isbn;
    m_title = _title;
    m_authors.swap(_authors);
    m_description = _description;
}

Book::~Book()
{
}

const std::string & Book::isbn() const {
    return m_isbn;
}

const std::string & Book::title() const {
    return m_title;
}

std::list<const Author *> Book::authors() const {
    std::list<const Author *> authors;
    for(const auto & a : m_authors)
    {
        authors.push_back(&(*a));
    }

    return authors;
}

const std::string & Book::description() const {
    return m_description;
}

namespace {
    void ensureValidForCreation(
        const std::string & _isbn,
        const std::string & _title,
        std::vector<std::unique_ptr<Author>> & _authors,
        const std::string &)
    {
        std::stringstream msg;

        if (_isbn.size() == 0) {
            msg << "Isbn '" << _isbn << "' is invalid";
            throw std::runtime_error(msg.str());
        }

        if (_title.size() == 0) {
            msg << "Title '" << _title << "' is invalid";
            throw std::runtime_error(msg.str());
        }

        if (_authors.size() == 0) {
            msg << "Book authors are invalid, expected 1 or more authors, "
                << "requested " << _authors.size();
            throw std::runtime_error(msg.str());
        }
    }
}
