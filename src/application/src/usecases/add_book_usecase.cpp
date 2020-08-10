#include "add_book_usecase.hpp"

#include <algorithm>
#include <memory>
#include <sstream>
#include <stdexcept>

#include <application/exceptions/book_already_exists_exception.hpp>
#include <application/exceptions/book_invalid_exception.hpp>

namespace
{
using MovableAuthors = std::unique_ptr<std::list<Author>>;
using Strings = std::list<std::string>;
MovableAuthors retrieveExistingAuthors(
    AuthorsRepositoryPort & _authors_repository, const Strings & _authors);
Book makeBook(const BookDTO & _book, MovableAuthors _authors);
void ensureBookNotExists(BooksRepositoryPort & _repo, Book & _book);
BookDTO storeBook(BooksRepositoryPort & _repo, Book & _book);
}

AddBookUsecase::AddBookUsecase(
    BooksRepositoryPort & _books_repository,
    AuthorsRepositoryPort & _authors_repository)
    : m_books_repository(_books_repository)
    , m_authors_repository(_authors_repository)
{
}

AddBookUsecase::~AddBookUsecase()
{
}

BookDTO AddBookUsecase::execute(const BookDTO & _book)
{
    auto existing_authors = retrieveExistingAuthors(
        m_authors_repository, _book.authors);

    auto book = makeBook(_book, std::move(existing_authors));

    ensureBookNotExists(m_books_repository, book);

    return storeBook(m_books_repository, book);
}

namespace
{
MovableAuthors retrieveExistingAuthors(
    AuthorsRepositoryPort & _authors_repository, const Strings & _authors)
{
    auto existing_authors = _authors_repository.findByNameIn(_authors);

    if (existing_authors.size() != _authors.size())
    {
        std::stringstream msg;
        msg << "Book authors are invalid,"
            <<" authors requested " << _authors.size()
            <<", authors found " << existing_authors.size();
        throw BookInvalidException(msg.str());
    }

    MovableAuthors authors(new std::list<Author>());
    std::for_each(
        existing_authors.begin(), existing_authors.end(),
        [& authors](const AuthorDTO & _author)
        { authors->push_back(Author(_author.name)); });

    return authors;
}

Book makeBook(const BookDTO & _book, MovableAuthors _authors)
{
    try
    {
        return Book(_book.isbn, _book.title, *_authors, _book.description);
    }
    catch (const std::runtime_error & _exc)
    {
        throw BookInvalidException(_exc.what());
    }
}

void ensureBookNotExists(BooksRepositoryPort & _repo, Book & _book)
{
    if (_repo.exists(_book.isbn()))
    {
        std::stringstream msg;
        msg << "Book with isbn '" << _book.isbn()
            << "' already exists";
        throw BookAlreadyExistsException(msg.str());
    }
}

BookDTO storeBook(BooksRepositoryPort & _repo, Book & _book)
{
    auto authors = _book.authors();
    Strings authors_str;
    std::for_each(
        authors.begin(), authors.end(),
        [& authors_str](const Author * _author)
        { authors_str.push_back(_author->name()); });

    return _repo.create({
            _book.isbn(),
            _book.title(),
            authors_str,
            _book.description()});
}
}
