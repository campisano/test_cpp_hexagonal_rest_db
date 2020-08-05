#ifndef AUTHORS_REPOSITORY_PORT__HPP__
#define AUTHORS_REPOSITORY_PORT__HPP__

#include <list>
#include <memory>
#include <string>

#include <application/dtos/author_dto.hpp>

class AuthorsRepositoryPort
{
public:
    virtual ~AuthorsRepositoryPort() = default;

public:
    virtual AuthorDTO create(const AuthorDTO & _author) = 0;
    virtual bool exists(const std::string & _name) = 0;
    virtual std::unique_ptr<AuthorDTO> findByName(
        const std::string & _name) = 0;
    virtual std::list<AuthorDTO> findByNameIn(
        const std::list<std::string> & _author_names) = 0;
};

#endif
