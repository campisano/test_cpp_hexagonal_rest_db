#ifndef HTTPLIB_HTTP_SERVER__HPP__
#define HTTPLIB_HTTP_SERVER__HPP__

#include <adapters/drivers/http_server.hpp>
#include <functional>
#include <httplib.h>
#include <memory>
#include <string>
#include <thread>

class HttplibHTTPServer : public HTTPServer
{
public:
    explicit HttplibHTTPServer();
    HttplibHTTPServer(const HttplibHTTPServer &) = delete;
    HttplibHTTPServer(HttplibHTTPServer &&) = default;
    virtual ~HttplibHTTPServer();

    HttplibHTTPServer & operator=(const HttplibHTTPServer &) = delete;
    HttplibHTTPServer & operator=(HttplibHTTPServer &&) = default;

public:
    virtual void start(
        const std::string & _ip,
        unsigned int _port,
        unsigned int _threads);

    virtual void wait();
    virtual void stop();

    void route(
        const std::string & _path,
        const std::string & _method,
        const std::function <void (
            const httplib::Request &,
            httplib::Response &)
        > & _handler);

private:
    std::unique_ptr<httplib::Server> m_service;
    std::unique_ptr<std::thread> m_thread_service;
};

#endif
