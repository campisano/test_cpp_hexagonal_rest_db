#include "restbed_http_health_check_controller.hpp"

#include <json.hpp>
#include <string>

#include "../drivers/http/restbed_http_server.hpp"
#include "../drivers/http/restbed_utils.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

RestbedHTTPHealthCheckController::RestbedHTTPHealthCheckController(
    HTTPServer & _server)
{
    RestbedHTTPServer & server = dynamic_cast<RestbedHTTPServer &>(_server);
    server.route(
        "/health", "GET",
        std::bind(
            &RestbedHTTPHealthCheckController::health,
            this,
            std::placeholders::_1));
}

RestbedHTTPHealthCheckController::~RestbedHTTPHealthCheckController()
{
}

void RestbedHTTPHealthCheckController::health(
    const std::shared_ptr< restbed::Session > _session)
{
    SpdlogLogger::info(__FILE__, "call to /health check");
    setJSONResponse(_session, restbed::OK, {{"status", "UP"}});
}
