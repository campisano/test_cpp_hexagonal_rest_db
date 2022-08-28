#include "httplib_http_books_controller.hpp"

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <application/exceptions/book_already_exists_exception.hpp>
#include <application/exceptions/book_invalid_exception.hpp>

#include "httplib_utils.hpp"
#include "../drivers/http/httplib_http_server.hpp"
#include "../drivers/logger/spdlog_logger.hpp"

HttplibHTTPBooksController::HttplibHTTPBooksController(
    AddBookUsecasePort & _add_book_usecase, HTTPServer & _server)
    : m_add_book_usecase(_add_book_usecase)
{
    HttplibHTTPServer & server = dynamic_cast<HttplibHTTPServer &>(_server);
    server.route(
        "/v1/books",
        "POST",
        std::bind(
            &HttplibHTTPBooksController::add,
            this,
            std::placeholders::_1,
            std::placeholders::_2));
}

HttplibHTTPBooksController::~HttplibHTTPBooksController()
{
}

void HttplibHTTPBooksController::add(
    const httplib::Request & _request,
    httplib::Response & _response)
{
    std::stringstream msg;
    msg << "add() requested, path" << _request.path << ", method " << _request.method << ", body " << _request.body;
    SpdlogLogger::info(__FILE__, msg.str());

    BookDTO book;

    try
    {
        auto json_body = nlohmann::json::parse(_request.body);
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
            _response, 400,
            {{"message", "Invalid request"}});
    }

    try
    {
        BookDTO new_book = m_add_book_usecase.execute(book);
        SpdlogLogger::info(
            __FILE__, std::string("created, book=") + book.isbn);
        setJSONResponse(
            _response, 200, {{"isbn", new_book.isbn}});
    }
    catch(const BookAlreadyExistsException & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Book already exists: ")
            + _exc.what());
        setJSONResponse(
            _response, 422,
            {{"message", "Book already exists"}});
    }
    catch(const BookInvalidException & _exc)
    {
        SpdlogLogger::error(
            __FILE__,
            std::string("Book invalid: ")
            + _exc.what());
        setJSONResponse(
            _response, 422,
            {{"message", "Invalid book"}});
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
