#include "postgresql_authors_repository.hpp"

#include <stdexcept>
#include <sstream>
#include "../drivers/logger/spdlog_logger.hpp"

PostgresqlAuthorsRepository::PostgresqlAuthorsRepository(
    Persistence & _persistence)
    : m_persistence(dynamic_cast<PostgresqlPersistence &>(_persistence))
{
    auto con = m_persistence.connection();
    pqxx::nontransaction w(*con);
    w.exec(
        "CREATE TABLE IF NOT EXISTS"
        " author "
        "( id   BIGSERIAL PRIMARY KEY"
        ", name TEXT "
        ")");
    w.exec(
        "CREATE UNIQUE INDEX IF NOT EXISTS"
        " author_name_ux ON author (name)");
    w.commit();
}

PostgresqlAuthorsRepository::~PostgresqlAuthorsRepository()
{
}

AuthorDTO PostgresqlAuthorsRepository::create(const AuthorDTO & _author)
{
    //TODO prepare only if not already exists
    auto con = m_persistence.connection();
    con->prepare(
        "PostgresqlAuthorsRepository::create",
        "INSERT INTO author (name) VALUES ($1) RETURNING id");

    pqxx::work txn {*con};
    auto id = txn.exec_prepared1(
        "PostgresqlAuthorsRepository::create", _author.name)[0].as<long>();
    txn.commit();

    std::stringstream msg;
    msg << "author created, id: " << id << ".";
    SpdlogLogger::debug(__FILE__, msg.str());

    return {_author.name};
}

bool PostgresqlAuthorsRepository::exists(const std::string & _name)
{
    auto con = m_persistence.connection();
    con->prepare(
        "PostgresqlAuthorsRepository::exists",
        "SELECT exists (SELECT 1 FROM author WHERE name = $1)");

    pqxx::work txn {*con};
    auto exists = txn.exec_prepared1(
        "PostgresqlAuthorsRepository::exists", _name)[0].as<bool>();
    txn.commit();

    std::stringstream msg;
    msg << "author exists, name: " << _name << ".";
    SpdlogLogger::debug(__FILE__, msg.str());

    return exists;
}

std::unique_ptr<AuthorDTO> PostgresqlAuthorsRepository::findByName(
    const std::string & _name)
{
    auto con = m_persistence.connection();
    con->prepare(
        "PostgresqlAuthorsRepository::findByName",
        "SELECT id, name FROM author WHERE name = $1");

    pqxx::work txn {*con};
    auto rows = txn.exec_prepared(
        "PostgresqlAuthorsRepository::findByName", _name);
    txn.commit();

    if(rows.size() == 0)
    {
        return std::unique_ptr<AuthorDTO>{};
    }

    if(rows.size() > 1)
    {
        throw std::runtime_error(
            "PostgresqlAuthorsRepository::findByName error"
            " returning more than one value");
    }

    std::string name = rows[0]["name"].c_str();

    std::stringstream msg;
    msg << "author retrieved, name: " << name << ".";
    SpdlogLogger::debug(__FILE__, msg.str());

    return std::unique_ptr<AuthorDTO>(new AuthorDTO {name});
}

std::list<AuthorDTO> PostgresqlAuthorsRepository::findByNameIn(
        const std::list<std::string> & _author_names)
{
    //TODO to implement seriously
    // there is no good way to do select .. in
    // https://stackoverflow.com/questions/23875183/how-to-perform-in-in-sql-query-using-pqxx-in-c-for-postgresql

    std::stringstream params;

    for (auto it = _author_names.begin(); it != _author_names.end(); ++it)
    {
        if(it != _author_names.begin())
        {
            params << ',';
        }
        params << '\'' << *it << '\'';
    }

    auto con = m_persistence.connection();
    con->prepare(
        "PostgresqlAuthorsRepository::findByNameIn",
        "SELECT name FROM author WHERE name IN ("
        + params.str() + ")");

    pqxx::work txn {*con};
    auto rows = txn.exec_prepared("PostgresqlAuthorsRepository::findByNameIn");
    txn.commit();

    std::list<AuthorDTO> authors;

    for(auto row : rows)
    {
        std::stringstream msg;
        msg << "author retrieved, name: " << row["name"].c_str() << ".";
        SpdlogLogger::error(__FILE__, msg.str());

        authors.push_back({row["name"].c_str()});
    }

    return authors;
}
