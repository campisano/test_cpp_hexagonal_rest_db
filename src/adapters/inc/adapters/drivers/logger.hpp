#ifndef LOGGER__HPP__
#define LOGGER__HPP__

#include <string>

class Logger
{
public:
    virtual ~Logger() = default;

public:
    virtual void setLoggerPath(const std::string & _path) = 0;
};

#endif
