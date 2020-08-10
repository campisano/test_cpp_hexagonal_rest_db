#ifndef RESTBED_HTTP_BOOKS_CONTROLLER__HPP__
#define RESTBED_HTTP_BOOKS_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>
#include <application/ports/usecases/add_book_usecase_port.hpp>

#include <memory>
#include <restbed>

class RestbedHTTPBooksController : public HTTPController
{
public:
    explicit RestbedHTTPBooksController(
        AddBookUsecasePort & _add_book_usecase, HTTPServer & _server);
    RestbedHTTPBooksController(const RestbedHTTPBooksController &) = delete;
    RestbedHTTPBooksController(RestbedHTTPBooksController &&) = default;
    virtual ~RestbedHTTPBooksController();

    RestbedHTTPBooksController & operator=(
        const RestbedHTTPBooksController &) = delete;
    RestbedHTTPBooksController & operator=(
        RestbedHTTPBooksController &&) = default;

public:
    void add(const std::shared_ptr< restbed::Session >);

private:
    AddBookUsecasePort & m_add_book_usecase;
};

#endif
