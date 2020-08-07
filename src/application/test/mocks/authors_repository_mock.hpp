#ifndef AUTHOR_REPOSITORY_MOCK__HPP__
#define AUTHOR_REPOSITORY_MOCK__HPP__

#include <application/ports/repositories/authors_repository_port.hpp>

class AuthorsRepositoryMock : public AuthorsRepositoryPort
{
public:
    static std::unique_ptr<AuthorsRepositoryMock> make()
    {
        return std::unique_ptr<AuthorsRepositoryMock>(
            new AuthorsRepositoryMock());
    }

    AuthorDTO create_in;
    AuthorDTO create_out;
    virtual AuthorDTO create(const AuthorDTO & _author)
    {
        create_in = _author;
        return create_out;
    }

    std::string exists_in;
    bool exists_out;
    virtual bool exists(const std::string & _name)
    {
        exists_in = _name;
        return exists_out;
    }

    std::string findByName_in;
    std::unique_ptr<AuthorDTO> findByName_out;
    virtual std::unique_ptr<AuthorDTO> findByName(
        const std::string & _name)
    {
        findByName_in = _name;
        return std::move(findByName_out);
    }

    std::list<std::string> findByNameIn_in;
    std::list<AuthorDTO> findByNameIn_out;
    virtual std::list<AuthorDTO> findByNameIn(
        const std::list<std::string> & _author_names)
    {
        findByNameIn_in = _author_names;
        return findByNameIn_out;
    }
};

#endif
