#include "postgresql_persistence.hpp"

#include "../logger/spdlog_logger.hpp"

PostgresqlPersistence::PostgresqlPersistence()
{
}

PostgresqlPersistence::~PostgresqlPersistence()
{
}

void PostgresqlPersistence::init(const std::string & _parameters)
{
    m_parameters = _parameters;
}

std::shared_ptr<pqxx::connection> PostgresqlPersistence::connection()
{
    //TODO make connection pool instead
    // see https://github.com/abzico/pqxx_pool
    return std::shared_ptr<pqxx::connection>(
        new pqxx::connection(m_parameters));
}
