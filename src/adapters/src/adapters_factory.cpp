#include <adapters/adapters_factory.hpp>

#include <sstream>
#include <stdexcept>
#include "controllers/httplib_http_authors_controller.hpp"
#include "controllers/httplib_http_books_controller.hpp"
#include "controllers/httplib_http_health_check_controller.hpp"
#include "drivers/http/httplib_http_server.hpp"
#include "drivers/logger/spdlog_logger.hpp"
#include "drivers/persistence/postgresql_persistence.hpp"
#include "drivers/config/json_config_loader.hpp"
#include "drivers/config/yaml_config_loader.hpp"
#include "repositories/postgresql_authors_repository.hpp"
#include "repositories/postgresql_books_repository.hpp"

AdaptersFactory::AdaptersFactory()
{
}

std::unique_ptr<ConfigLoader> AdaptersFactory::makeConfigLoader(
    const std::string & _driver)
{
    if(_driver == "json")
    {
        return std::unique_ptr<ConfigLoader>(new JsonConfigLoader());
    }
    else if (_driver == "yaml")
    {
        return std::unique_ptr<ConfigLoader>(new YamlConfigLoader());
    }

    std::stringstream msg;
    msg << "Specified config driver '" << _driver << "' is invalid";
    throw std::runtime_error(msg.str());
}

std::unique_ptr<Logger> AdaptersFactory::makeLogger()
{
    return std::unique_ptr<Logger>(new SpdlogLogger());
}

std::unique_ptr<Persistence> AdaptersFactory::makePersistence(
    const std::string & _driver)
{
    if (_driver == "postgres")
    {
        return std::unique_ptr<Persistence>(new PostgresqlPersistence());
    }

    std::stringstream msg;
    msg << "Specified persistence driver '" << _driver << "' is invalid";
    throw std::runtime_error(msg.str());
}

std::unique_ptr<AuthorsRepositoryPort> AdaptersFactory::makeAuthorsRepository(
    Persistence & _persistence)
{
    return std::unique_ptr<AuthorsRepositoryPort>(
        new PostgresqlAuthorsRepository(_persistence));
}

std::unique_ptr<BooksRepositoryPort> AdaptersFactory::makeBooksRepository(
    Persistence & _persistence)
{
    return std::unique_ptr<BooksRepositoryPort>(
        new PostgresqlBooksRepository(_persistence));
}

std::unique_ptr<HTTPServer> AdaptersFactory::makeHTTPServer()
{
    return std::unique_ptr<HTTPServer>(new HttplibHTTPServer());
}

std::unique_ptr<HTTPController> AdaptersFactory::makeHTTPHealthCheckController(
    HTTPServer & _server)
{
    return std::unique_ptr<HTTPController>(
        new HttplibHTTPHealthCheckController(_server));
}

std::unique_ptr<HTTPController> AdaptersFactory::makeHTTPAuthorsController(
    AddAuthorUsecasePort & _usecase, HTTPServer & _server)
{
    return std::unique_ptr<HTTPController>(
        new HttplibHTTPAuthorsController(_usecase, _server));
}

std::unique_ptr<HTTPController> AdaptersFactory::makeHTTPBooksController(
    AddBookUsecasePort & _usecase, HTTPServer & _server)
{
    return std::unique_ptr<HTTPController>(
        new HttplibHTTPBooksController(_usecase, _server));
}
