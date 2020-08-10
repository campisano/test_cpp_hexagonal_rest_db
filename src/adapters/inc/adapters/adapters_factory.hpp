#ifndef ADAPTERS_FACTORY__HPP__
#define ADAPTERS_FACTORY__HPP__

#include <memory>

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/config_loader.hpp>
#include <adapters/drivers/http_server.hpp>
#include <adapters/drivers/logger.hpp>
#include <adapters/drivers/persistence.hpp>
#include <application/ports/repositories/authors_repository_port.hpp>
#include <application/ports/repositories/books_repository_port.hpp>
#include <application/ports/usecases/add_author_usecase_port.hpp>
#include <application/ports/usecases/add_book_usecase_port.hpp>

class AdaptersFactory
{
private:
    explicit AdaptersFactory();

public:
    static std::unique_ptr<ConfigLoader> makeConfigLoader(
        const std::string & _driver);
    static std::unique_ptr<Logger> makeLogger();
    static std::unique_ptr<Persistence> makePersistence(
        const std::string & _driver);

    static std::unique_ptr<AuthorsRepositoryPort> makeAuthorsRepository(
        Persistence & _persistence);
    static std::unique_ptr<BooksRepositoryPort> makeBooksRepository(
        Persistence & _persistence);

    static std::unique_ptr<HTTPServer> makeHTTPServer();
    static std::unique_ptr<HTTPController> makeHTTPHealthCheckController(
        HTTPServer & _server);

    static std::unique_ptr<HTTPController> makeHTTPAuthorsController(
        AddAuthorUsecasePort & _usecase, HTTPServer & _server);

    static std::unique_ptr<HTTPController> makeHTTPBooksController(
        AddBookUsecasePort & _usecase, HTTPServer & _server);
};

#endif
