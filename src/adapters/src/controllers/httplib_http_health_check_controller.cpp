#include "httplib_http_health_check_controller.hpp"

#include <json.hpp>
#include <sstream>
#include <string>

#include "httplib_utils.hpp"
#include "../drivers/http/httplib_http_server.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

HttplibHTTPHealthCheckController::HttplibHTTPHealthCheckController(
    HTTPServer & _server)
{
    HttplibHTTPServer & server = dynamic_cast<HttplibHTTPServer &>(_server);
    server.route(
        "/health",
        "GET",
        std::bind(
            &HttplibHTTPHealthCheckController::health,
            this,
            std::placeholders::_1,
            std::placeholders::_2));
}

HttplibHTTPHealthCheckController::~HttplibHTTPHealthCheckController()
{
}

void HttplibHTTPHealthCheckController::health(
    const httplib::Request & _request,
    httplib::Response & _response)
{
    std::stringstream msg;
    msg << "health() requested, path" << _request.path << ", method " << _request.method << ", body " << _request.body;
    SpdlogLogger::info(__FILE__, msg.str());

    setJSONResponse(_response, 200, {{"status", "UP"}});
}
