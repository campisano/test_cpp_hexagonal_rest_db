#ifndef CONFIG__HPP__
#define CONFIG__HPP__

#include <string>

struct Config
{
    struct Logger
    {
        std::string path;
    };
    struct Persistence
    {
        std::string driver;
        std::string parameters;
    };
    struct Http
    {
        std::string host;
        int port;
        int threads;
    };

    Logger logger;
    Persistence persistence;
    Http http;
};

#endif
