#include "restbed_http_authors_controller.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <application/exceptions/author_already_exists_exception.hpp>
#include <application/exceptions/author_invalid_exception.hpp>

#include "../drivers/http/restbed_http_server.hpp"
#include "../drivers/http/restbed_utils.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

RestbedHTTPAuthorsController::RestbedHTTPAuthorsController(
    AddAuthorUsecasePort & _add_author_usecase, HTTPServer & _server)
    : m_add_author_usecase(_add_author_usecase)
{
    RestbedHTTPServer & server = dynamic_cast<RestbedHTTPServer &>(_server);
    server.route(
        "/v1/authors", "POST",
        std::bind(
            &RestbedHTTPAuthorsController::add,
            this,
            std::placeholders::_1));
}

RestbedHTTPAuthorsController::~RestbedHTTPAuthorsController()
{
}

void RestbedHTTPAuthorsController::add(
    const std::shared_ptr< restbed::Session > _session)
{
    SpdlogLogger::info(__FILE__, "add()");

    const auto request = _session->get_request( );
    const auto transfer_encoding = request->get_header(
        "Transfer-Encoding", restbed::String::lowercase);

    if(
        transfer_encoding == "chunked"
        || ! request->has_header("Content-Length"))
    {
        SpdlogLogger::error(
            __FILE__, "Bad request: chunked Transfer-Encoding not supported");
        _session->close(restbed::BAD_REQUEST);
        return;
    }

    auto content_length = request->get_header("Content-Length", 0);

    _session->fetch(
        content_length,
        [request, this](
            const std::shared_ptr< restbed::Session > session,
            const restbed::Bytes & body)
        {
            SpdlogLogger::info(
                __FILE__,
                std::string(request->get_path())
                + " " + request->get_method());
            AuthorDTO author;

            try
            {
                auto json_body = nlohmann::json::parse(body);
                json_body.at("name").get_to(author.name);
            }
            catch(const std::exception & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Bad request: error parsing body ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::BAD_REQUEST,
                    {{"message", "Invalid request"}});
            }

            try
            {
                AuthorDTO new_author = m_add_author_usecase.execute(author);
                SpdlogLogger::info(
                    __FILE__, std::string("created, author=") + author.name);
                setJSONResponse(
                    session, restbed::OK, {{"name", new_author.name}});
            }
            catch(const AuthorAlreadyExistsException & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Author already exists: ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::UNPROCESSABLE_ENTITY,
                    {{"message", "An author already exist"}});
            }
            catch(const AuthorInvalidException & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Author invalid: ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::UNPROCESSABLE_ENTITY,
                    {{"message", "Invalid author"}});
            }
            catch(const std::exception & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Internal server error: ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::INTERNAL_SERVER_ERROR,
                    {{"message", "Internal server error"}});
            }
        });
}
