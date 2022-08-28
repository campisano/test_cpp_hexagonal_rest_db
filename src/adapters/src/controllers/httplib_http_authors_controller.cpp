#include "httplib_http_authors_controller.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>

#include "httplib_utils.hpp"
#include "../drivers/http/httplib_http_server.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

HttplibHTTPAuthorsController::HttplibHTTPAuthorsController(
    AddAuthorUsecasePort & _add_author_usecase, HTTPServer & _server)
    : m_add_author_usecase(_add_author_usecase)
{
    HttplibHTTPServer & server = dynamic_cast<HttplibHTTPServer &>(_server);
    server.route(
        "/v1/authors",
        "POST",
        std::bind(
            &HttplibHTTPAuthorsController::add,
            this,
            std::placeholders::_1,
            std::placeholders::_2));
}

HttplibHTTPAuthorsController::~HttplibHTTPAuthorsController()
{
}

void HttplibHTTPAuthorsController::add(
    const httplib::Request & _request,
    httplib::Response & _response)
{
    std::stringstream msg;
    msg << "add() requested, path" << _request.path << ", method " << _request.method << ", body " << _request.body;
    SpdlogLogger::info(__FILE__, msg.str());

    AuthorDTO author;

    try
    {
        auto json_body = nlohmann::json::parse(_request.body);
        json_body.at("name").get_to(author.name);
    }
    catch(const std::exception & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Bad request: error parsing body ")
            + _exc.what());
        setJSONResponse(
            _response, 400,
            {{"message", "Invalid request"}});
    }

    try
    {
        AuthorDTO new_author = m_add_author_usecase.execute(author);
        SpdlogLogger::info(
            __FILE__, std::string("created, author=") + author.name);
        setJSONResponse(
            _response, 200, {{"name", new_author.name}});
    }
    catch(const AuthorAlreadyExistsException & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Author already exists: ")
            + _exc.what());
        setJSONResponse(
            _response, 422,
            {{"message", "Author already exists"}});
    }
    catch(const AuthorInvalidException & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Author invalid: ")
            + _exc.what());
        setJSONResponse(
            _response, 422,
            {{"message", "Invalid author"}});
    }
    catch(const std::exception & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Internal server error: ")
            + _exc.what());
        setJSONResponse(
            _response, 500,
            {{"message", "Internal server error"}});
    }
}
