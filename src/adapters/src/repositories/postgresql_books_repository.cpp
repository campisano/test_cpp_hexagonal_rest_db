#include "postgresql_books_repository.hpp"

#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include "../drivers/logger/spdlog_logger.hpp"

namespace
{
std::list<long> findAuthorIds(
    pqxx::connection & _con,
    pqxx::work & _txn,
    std::list<std::string> _authors);
void insertAuthorBookIds(
    pqxx::connection & _con,
    pqxx::work & _txn,
    const long _book_id,
    const std::list<long> & _authors_ids);
}

PostgresqlBooksRepository::PostgresqlBooksRepository(
    Persistence & _persistence)
    : m_persistence(dynamic_cast<PostgresqlPersistence &>(_persistence))
{
    auto con = m_persistence.connection();
    pqxx::nontransaction w(*con);
    w.exec(
        "CREATE TABLE IF NOT EXISTS"
        " book "
        "( id          BIGSERIAL PRIMARY KEY"
        ", isbn        TEXT NOT NULL"
        ", title       TEXT NOT NULL"
        ", description TEXT "
        ")");
    w.exec(
        "CREATE UNIQUE INDEX IF NOT EXISTS"
        " book_isbn_ux ON book (isbn)");
    w.exec(
        "CREATE TABLE IF NOT EXISTS"
        " author_book "
        "( author_id BIGINT NOT NULL"
        ", book_id BIGINT NOT NULL"
        ", CONSTRAINT author_book_author_id_fk"
        " FOREIGN KEY (author_id) REFERENCES author (id)"
        ", CONSTRAINT author_book_book_id_fk"
        " FOREIGN KEY (book_id) REFERENCES book (id)"
        ")");
    w.exec(
        "CREATE UNIQUE INDEX IF NOT EXISTS"
        " author_book_ux ON author_book (author_id, book_id)");
    w.commit();
}

PostgresqlBooksRepository::~PostgresqlBooksRepository()
{
}

BookDTO PostgresqlBooksRepository::create(const BookDTO & _book)
{
    //TODO prepare only if not already exists
    const std::string stm_name = "PostgresqlBooksRepository::create";
    auto con = m_persistence.connection();
    con->prepare(
        stm_name,
        "INSERT INTO book (isbn, title, description)"
        " VALUES ($1, $2, $3) RETURNING id");

    pqxx::work txn {*con};
    auto id = txn.exec_prepared1(
        stm_name,
        _book.isbn,
        _book.title,
        _book.description
        )[0].as<long>();

    std::stringstream msg;
    msg << "book created, id: " << id << ".";
    SpdlogLogger::debug(__FILE__, msg.str());

    auto authors_ids = findAuthorIds(*con, txn, _book.authors);
    insertAuthorBookIds(*con, txn, id, authors_ids);

    txn.commit();

    return {_book.isbn, _book.title, {"author1"}, _book.description};
}

bool PostgresqlBooksRepository::exists(const std::string & _isbn)
{
    const std::string stm_name = "PostgresqlBooksRepository::exists";
    auto con = m_persistence.connection();
    con->prepare(
        stm_name,
        "SELECT exists (SELECT 1 FROM book WHERE isbn = $1)");

    pqxx::work txn {*con};
    auto exists = txn.exec_prepared1(stm_name, _isbn)[0].as<bool>();
    txn.commit();

    std::stringstream msg;
    msg << "book with isbn '" << _isbn << "' exists=" << exists << ".";
    SpdlogLogger::debug(__FILE__, msg.str());

    return exists;
}

namespace
{
std::list<long> findAuthorIds(
    pqxx::connection & _con,
    pqxx::work & _txn,
    std::list<std::string> _authors)
{
    //TODO to implement seriously
    // there is no good way to do select .. in
    // https://stackoverflow.com/questions/23875183/how-to-perform-in-in-sql-query-using-pqxx-in-c-for-postgresql

    std::stringstream params;
    std::copy(
        _authors.begin(), _authors.end(),
        std::ostream_iterator<std::string>(params, "','"));

    const std::string stm_name = "PostgresqlBooksRepository::findAuthorIds";
    _con.prepare(
        stm_name,
        "SELECT id FROM author WHERE name IN ('"
        + params.str() + "')");

    auto rows = _txn.exec_prepared(stm_name);

    std::list<long> author_ids;

    for(auto row : rows)
    {
        author_ids.push_back({row["id"].as<long>()});
    }

    return author_ids;
}

void insertAuthorBookIds(
    pqxx::connection & _con,
    pqxx::work & _txn,
    const long _book_id,
    const std::list<long> & _authors_ids)
{
    const std::string stm_name =
        "PostgresqlBooksRepository::insertAuthorBookIds";
    _con.prepare(
        stm_name,
        "INSERT INTO author_book (author_id, book_id)"
        " VALUES ($1, $2)");

    for(auto id : _authors_ids)
    {
        _txn.exec_prepared0(stm_name, id, _book_id);
    }
}
}
