#ifndef HTTPLIB_HTTP_AUTHORS_CONTROLLER__HPP__
#define HTTPLIB_HTTP_AUTHORS_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>
#include <application/ports/usecases/add_author_usecase_port.hpp>

#include <httplib.h>
#include <memory>

class HttplibHTTPAuthorsController : public HTTPController
{
public:
    explicit HttplibHTTPAuthorsController(
        AddAuthorUsecasePort & _add_author_usecase, HTTPServer & _server);
    HttplibHTTPAuthorsController(const HttplibHTTPAuthorsController &) = delete;
    HttplibHTTPAuthorsController(HttplibHTTPAuthorsController &&) = default;
    virtual ~HttplibHTTPAuthorsController();

    HttplibHTTPAuthorsController & operator=(
        const HttplibHTTPAuthorsController &) = delete;
    HttplibHTTPAuthorsController & operator=(
        HttplibHTTPAuthorsController &&) = default;

public:
    void add(
        const httplib::Request &,
        httplib::Response &);

private:
    AddAuthorUsecasePort & m_add_author_usecase;
};

#endif
