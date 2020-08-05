#ifndef RESTBED_HTTP_HEALTH_CHECK_CONTROLLER__HPP__
#define RESTBED_HTTP_HEALTH_CHECK_CONTROLLER__HPP__

#include <adapters/controllers/http_controller.hpp>
#include <adapters/drivers/http_server.hpp>

#include <memory>
#include <restbed>

class RestbedHTTPHealthCheckController : public HTTPController
{
public:
    explicit RestbedHTTPHealthCheckController(
        HTTPServer & _server);
    RestbedHTTPHealthCheckController(
        const RestbedHTTPHealthCheckController &) = delete;
    RestbedHTTPHealthCheckController(
        RestbedHTTPHealthCheckController &&) = default;
    virtual ~RestbedHTTPHealthCheckController();

    RestbedHTTPHealthCheckController & operator=(
        const RestbedHTTPHealthCheckController &) = delete;
    RestbedHTTPHealthCheckController & operator=(
        RestbedHTTPHealthCheckController &&) = default;

public:
    void health(const std::shared_ptr< restbed::Session >);
};

#endif
