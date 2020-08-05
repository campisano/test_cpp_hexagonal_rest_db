#ifndef JSON_CONFIG_LOADER__HPP__
#define JSON_CONFIG_LOADER__HPP__

#include <string>
#include <adapters/drivers/config_loader.hpp>

class JsonConfigLoader : public ConfigLoader
{
public:
    explicit JsonConfigLoader();
    JsonConfigLoader(const JsonConfigLoader &) = delete;
    JsonConfigLoader(JsonConfigLoader &&) = default;
    virtual ~JsonConfigLoader();

    JsonConfigLoader & operator=(const JsonConfigLoader &) = delete;
    JsonConfigLoader & operator=(JsonConfigLoader &&) = default;

public:
    virtual Config load(const std::string & _file_path);
};

#endif
