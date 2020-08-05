#include "spdlog_logger.hpp"

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace
{
    std::shared_ptr<spdlog::logger> getLogger(std::string _name)
    {
        auto logger = spdlog::get(_name);

        if(!logger)
        {
            auto sinks = spdlog::get("root")->sinks();
            logger = std::make_shared<spdlog::logger>(
                _name, begin(sinks), end(sinks));
            logger->flush_on(spdlog::level::info);
        }

        return logger;
    }
}

SpdlogLogger::SpdlogLogger()
{
}

SpdlogLogger::~SpdlogLogger()
{
}

void SpdlogLogger::setLoggerPath(const std::string & _path)
{
    std::vector<spdlog::sink_ptr> sinks;

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    sinks.push_back(console_sink);

    auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
        _path, 0, 0);
    file_sink->set_level(spdlog::level::trace);
    sinks.push_back(file_sink);

    auto root_logger = std::make_shared<spdlog::logger>(
        "root", begin(sinks), end(sinks));
    root_logger->flush_on(spdlog::level::info);
    spdlog::set_default_logger(root_logger);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %z] [%^%=7l%$] [%n] %v");
}

void SpdlogLogger::debug(
    const std::string & _name, const std::string & _message)
{
    getLogger(_name)->debug(_message);
}

void SpdlogLogger::info(
    const std::string & _name, const std::string & _message)
{
    getLogger(_name)->info(_message);
}

void SpdlogLogger::warn(
    const std::string & _name, const std::string & _message)
{
    getLogger(_name)->warn(_message);
}

void SpdlogLogger::error(
    const std::string & _name, const std::string & _message)
{
    getLogger(_name)->error(_message);
}
