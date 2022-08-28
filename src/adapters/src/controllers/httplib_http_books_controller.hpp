#ifndef HTTPLIB_HTTP_BOOKS_CONTROLLER__HPP__
#define HTTPLIB_HTTP_BOOKS_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>
#include <application/ports/usecases/add_book_usecase_port.hpp>

#include <httplib.h>
#include <memory>

class HttplibHTTPBooksController : public HTTPController
{
public:
    explicit HttplibHTTPBooksController(
        AddBookUsecasePort & _add_book_usecase, HTTPServer & _server);
    HttplibHTTPBooksController(const HttplibHTTPBooksController &) = delete;
    HttplibHTTPBooksController(HttplibHTTPBooksController &&) = default;
    virtual ~HttplibHTTPBooksController();

    HttplibHTTPBooksController & operator=(
        const HttplibHTTPBooksController &) = delete;
    HttplibHTTPBooksController & operator=(
        HttplibHTTPBooksController &&) = default;

public:
    void add(
        const httplib::Request &,
        httplib::Response &);

private:
    AddBookUsecasePort & m_add_book_usecase;
};

#endif
