#ifndef HTTP_SERVER__HPP__
#define HTTP_SERVER__HPP__

#include <string>

class HTTPServer
{
public:
    virtual ~HTTPServer() = default;

public:
    virtual void start(
        const std::string & _ip,
        unsigned int _port,
        unsigned int _threads) = 0;

    virtual void wait() = 0;
    virtual void stop() = 0;
};

#endif
