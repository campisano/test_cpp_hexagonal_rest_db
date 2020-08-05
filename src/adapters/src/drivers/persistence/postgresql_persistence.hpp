#ifndef POSTGRESQL_PERSISTENCE__HPP__
#define POSTGRESQL_PERSISTENCE__HPP__

#include <adapters/drivers/persistence.hpp>
#include <memory>
#include <pqxx/pqxx>
#include <string>

class PostgresqlPersistence : public Persistence
{
public:
    explicit PostgresqlPersistence();
    PostgresqlPersistence(const PostgresqlPersistence &) = delete;
    PostgresqlPersistence(PostgresqlPersistence &&) = default;
    virtual ~PostgresqlPersistence();

    PostgresqlPersistence & operator=(const PostgresqlPersistence &) = delete;
    PostgresqlPersistence & operator=(PostgresqlPersistence &&) = default;

public:
    virtual void init(const std::string & _parameters);
    std::shared_ptr<pqxx::connection> connection();

private:
    std::string m_parameters;
};

#endif
