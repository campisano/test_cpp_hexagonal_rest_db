#ifndef HTTPLIB_HTTP_HEALTH_CHECK_CONTROLLER__HPP__
#define HTTPLIB_HTTP_HEALTH_CHECK_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>

#include <httplib.h>
#include <memory>

class HttplibHTTPHealthCheckController : public HTTPController
{
public:
    explicit HttplibHTTPHealthCheckController(
        HTTPServer & _server);
    HttplibHTTPHealthCheckController(
        const HttplibHTTPHealthCheckController &) = delete;
    HttplibHTTPHealthCheckController(
        HttplibHTTPHealthCheckController &&) = default;
    virtual ~HttplibHTTPHealthCheckController();

    HttplibHTTPHealthCheckController & operator=(
        const HttplibHTTPHealthCheckController &) = delete;
    HttplibHTTPHealthCheckController & operator=(
        HttplibHTTPHealthCheckController &&) = default;

public:
    void health(
        const httplib::Request &,
        httplib::Response &);
};

#endif
