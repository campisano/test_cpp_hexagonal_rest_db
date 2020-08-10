#ifndef POSTGRESQL_BOOKS_REPOSITORY__HPP__
#define POSTGRESQL_BOOKS_REPOSITORY__HPP__

#include <adapters/drivers/persistence.hpp>
#include <application/ports/repositories/books_repository_port.hpp>
#include "../drivers/persistence/postgresql_persistence.hpp"

class PostgresqlBooksRepository : public BooksRepositoryPort
{
public:
    explicit PostgresqlBooksRepository(Persistence & _persistence);
    PostgresqlBooksRepository(const PostgresqlBooksRepository &) = delete;
    PostgresqlBooksRepository(PostgresqlBooksRepository &&) = default;
    virtual ~PostgresqlBooksRepository();

    PostgresqlBooksRepository & operator=(
        const PostgresqlBooksRepository &) = delete;
    PostgresqlBooksRepository & operator=(
        PostgresqlBooksRepository &&) = default;

public:
    virtual BookDTO create(const BookDTO & _book);
    virtual bool exists(const std::string & _isbn);

private:
    PostgresqlPersistence & m_persistence;
};

#endif
