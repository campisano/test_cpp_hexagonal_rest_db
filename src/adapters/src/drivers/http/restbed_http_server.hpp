#ifndef RESTBED_HTTP_SERVER__HPP__
#define RESTBED_HTTP_SERVER__HPP__

#include <adapters/drivers/http_server.hpp>
#include <memory>
#include <restbed>
#include <string>

class RestbedHTTPServer : public HTTPServer
{
public:
    explicit RestbedHTTPServer();
    RestbedHTTPServer(const RestbedHTTPServer &) = delete;
    RestbedHTTPServer(RestbedHTTPServer &&) = default;
    virtual ~RestbedHTTPServer();

    RestbedHTTPServer & operator=(const RestbedHTTPServer &) = delete;
    RestbedHTTPServer & operator=(RestbedHTTPServer &&) = default;

public:
    virtual void start(
        const std::string & _ip,
        unsigned int _port,
        unsigned int _threads);

    virtual void wait();
    virtual void stop();

    void notFound(
        const std::function <void (
            const std::shared_ptr< restbed::Session >)
        > & _handler);

    void route(
        const std::string & _path,
        const std::string & _method,
        const std::function <void (
            const std::shared_ptr< restbed::Session >)
        > & _handler);

private:
    void handle_startup_message(restbed::Service &);

    std::unique_ptr<restbed::Service> m_service;
    std::unique_ptr<std::thread> m_thread_service;
};

#endif
