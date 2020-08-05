#ifndef YAML_CONFIG_LOADER__HPP__
#define YAML_CONFIG_LOADER__HPP__

#include <string>
#include <adapters/drivers/config_loader.hpp>

class YamlConfigLoader : public ConfigLoader
{
public:
    virtual Config load(const std::string & _file_path);
};

#endif
