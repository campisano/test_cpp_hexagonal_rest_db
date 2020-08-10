#include "restbed_http_books_controller.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <application/exceptions/book_already_exists_exception.hpp>
#include <application/exceptions/book_invalid_exception.hpp>

#include "../drivers/http/restbed_http_server.hpp"
#include "../drivers/http/restbed_utils.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

RestbedHTTPBooksController::RestbedHTTPBooksController(
    AddBookUsecasePort & _add_book_usecase, HTTPServer & _server)
    : m_add_book_usecase(_add_book_usecase)
{
    RestbedHTTPServer & server = dynamic_cast<RestbedHTTPServer &>(_server);
    server.route(
        "/v1/books", "POST",
        std::bind(
            &RestbedHTTPBooksController::add,
            this,
            std::placeholders::_1));
}

RestbedHTTPBooksController::~RestbedHTTPBooksController()
{
}

void RestbedHTTPBooksController::add(
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
            BookDTO book;

            try
            {
                auto json_body = nlohmann::json::parse(body);
                json_body.at("isbn").get_to(book.isbn);
                json_body.at("title").get_to(book.title);
                json_body.at("authors").get_to(book.authors);
                json_body.at("description").get_to(book.description);
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
                BookDTO new_book = m_add_book_usecase.execute(book);
                SpdlogLogger::info(
                    __FILE__, std::string("created, book=") + book.isbn);
                setJSONResponse(
                    session, restbed::OK, {{"isbn", new_book.isbn}});
            }
            catch(const BookAlreadyExistsException & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Book already exists: ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::UNPROCESSABLE_ENTITY,
                    {{"message", "Book already exists"}});
            }
            catch(const BookInvalidException & _exc)
            {
                SpdlogLogger::error(
                    __FILE__,
                    std::string("Book invalid: ")
                    + _exc.what());
                setJSONResponse(
                    session, restbed::UNPROCESSABLE_ENTITY,
                    {{"message", "Invalid book"}});
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
