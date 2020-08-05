#include "yaml_config_loader.hpp"

#include <yaml-cpp/yaml.h>
#include <string>

YamlConfigLoader::YamlConfigLoader()
{
}

YamlConfigLoader::~YamlConfigLoader()
{
}

Config YamlConfigLoader::load(const std::string & _file_path)
{
    YAML::Node y = YAML::LoadFile(_file_path);

    Config::Logger log_cfg
    {
        y["logger"]["path"].as<std::string>()
    };

    Config::Persistence per_cfg
    {
        y["persistence"]["driver"].as<std::string>(),
        y["persistence"]["parameters"].as<std::string>()
    };

    Config::Http http_cfg
    {
        y["http"]["host"].as<std::string>(),
        y["http"]["port"].as<int>(),
        y["http"]["threads"].as<int>()
    };

    return Config{log_cfg, per_cfg, http_cfg};
}
