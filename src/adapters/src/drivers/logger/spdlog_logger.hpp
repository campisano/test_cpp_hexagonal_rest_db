#ifndef SPDLOG_LOGGER__HPP__
#define SPDLOG_LOGGER__HPP__

#include <adapters/drivers/logger.hpp>
#include <string>

class SpdlogLogger : public Logger
{
public:
    explicit SpdlogLogger();
    SpdlogLogger(const SpdlogLogger &) = delete;
    SpdlogLogger(SpdlogLogger &&) = default;
    virtual ~SpdlogLogger();

    SpdlogLogger & operator=(const SpdlogLogger &) = delete;
    SpdlogLogger & operator=(SpdlogLogger &&) = default;

public:
    virtual void setLoggerPath(const std::string & _path);

    static void debug(const std::string & _name, const std::string & _message);
    static void info(const std::string & _name, const std::string & _message);
    static void warn(const std::string & _name, const std::string & _message);
    static void error(const std::string & _name, const std::string & _message);
};

#endif
