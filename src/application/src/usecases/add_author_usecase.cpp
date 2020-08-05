#include "add_author_usecase.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>

namespace
{
    std::unique_ptr<Author> makeAuthor(const AuthorDTO & _author);
}

AddAuthorUsecase::AddAuthorUsecase(AuthorsRepositoryPort & _authors_repository)
    : m_authors_repository(_authors_repository)
{
}

AddAuthorUsecase::~AddAuthorUsecase()
{
}

AuthorDTO AddAuthorUsecase::execute(const AuthorDTO & _author)
{
    auto author = makeAuthor(_author);

    if (m_authors_repository.exists(author->name()))
    {
        std::stringstream msg;
        msg << "Author with name '" << author->name()
            << " already exists";
        throw AuthorAlreadyExistsException(msg.str());
    }

    m_authors_repository.create({author->name()});

    return {author->name()};
}

namespace
{
    std::unique_ptr<Author> makeAuthor(const AuthorDTO & _author)
    {
        try
        {
            return std::unique_ptr<Author>(new Author(_author.name));
        }
        catch (const std::runtime_error & _exc)
        {
            throw AuthorInvalidException(_exc.what());
        }
    }
}
