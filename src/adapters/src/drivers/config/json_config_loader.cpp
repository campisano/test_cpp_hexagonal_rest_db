#include "json_config_loader.hpp"

#include <fstream>
#include <json.hpp>
#include <string>

JsonConfigLoader::JsonConfigLoader()
{
}

JsonConfigLoader::~JsonConfigLoader()
{
}

Config JsonConfigLoader::load(const std::string & _file_path)
{
    std::ifstream config_file(_file_path);
    nlohmann::json j = nlohmann::json::parse(config_file);

    Config::Logger log_cfg
    {
        j["logger"]["path"].get<std::string>()
    };

    Config::Persistence per_cfg
    {
        j["persistence"]["driver"].get<std::string>(),
        j["persistence"]["parameters"].get<std::string>()
    };

    Config::Http http_cfg
    {
        j["http"]["host"].get<std::string>(),
        j["http"]["port"].get<int>(),
        j["http"]["threads"].get<int>()
    };

    return Config{log_cfg, per_cfg, http_cfg};
}
