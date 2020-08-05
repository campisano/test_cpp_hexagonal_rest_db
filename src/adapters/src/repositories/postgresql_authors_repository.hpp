#ifndef POSTGRESQL_AUTHORS_REPOSITORY__HPP__
#define POSTGRESQL_AUTHORS_REPOSITORY__HPP__

#include <adapters/drivers/persistence.hpp>
#include <application/ports/repositories/authors_repository_port.hpp>
#include "../drivers/persistence/postgresql_persistence.hpp"

class PostgresqlAuthorsRepository : public AuthorsRepositoryPort
{
public:
    explicit PostgresqlAuthorsRepository(Persistence & _persistence);
    PostgresqlAuthorsRepository(const PostgresqlAuthorsRepository &) = delete;
    PostgresqlAuthorsRepository(PostgresqlAuthorsRepository &&) = default;
    virtual ~PostgresqlAuthorsRepository();

    PostgresqlAuthorsRepository & operator=(
        const PostgresqlAuthorsRepository &) = delete;
    PostgresqlAuthorsRepository & operator=(
        PostgresqlAuthorsRepository &&) = default;

public:
    virtual AuthorDTO create(const AuthorDTO & _author);
    virtual bool exists(const std::string & _name);
    virtual std::unique_ptr<AuthorDTO> findByName(
        const std::string & _name);
    virtual std::list<AuthorDTO> findByNameIn(
        const std::list<std::string> & _author_names);

private:
    PostgresqlPersistence & m_persistence;
};

#endif
