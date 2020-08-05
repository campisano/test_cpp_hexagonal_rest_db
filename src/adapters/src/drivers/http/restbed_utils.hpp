#ifndef RESTBED_UTILS__HPP__
#define RESTBED_UTILS__HPP__

#include <json.hpp>
#include <restbed>

void setJSONResponse(
    const std::shared_ptr< restbed::Session > & _session,
    int _status,
    nlohmann::json _body);

#endif
