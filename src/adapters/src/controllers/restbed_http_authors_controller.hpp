#ifndef RESTBED_HTTP_AUTHORS_CONTROLLER__HPP__
#define RESTBED_HTTP_AUTHORS_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>
#include <application/ports/usecases/add_author_usecase_port.hpp>

#include <memory>
#include <restbed>

class RestbedHTTPAuthorsController : public HTTPController
{
public:
    explicit RestbedHTTPAuthorsController(
        AddAuthorUsecasePort & _add_author_usecase, HTTPServer & _server);
    RestbedHTTPAuthorsController(const RestbedHTTPAuthorsController &) = delete;
    RestbedHTTPAuthorsController(RestbedHTTPAuthorsController &&) = default;
    virtual ~RestbedHTTPAuthorsController();

    RestbedHTTPAuthorsController & operator=(
        const RestbedHTTPAuthorsController &) = delete;
    RestbedHTTPAuthorsController & operator=(
        RestbedHTTPAuthorsController &&) = default;

    void add(const std::shared_ptr< restbed::Session >);

private:
    AddAuthorUsecasePort & m_add_author_usecase;
};

#endif
