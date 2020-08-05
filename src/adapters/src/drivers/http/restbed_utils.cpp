#include "restbed_utils.hpp"

#include <string>

void setJSONResponse(
    const std::shared_ptr< restbed::Session > & _session,
    int _status,
    nlohmann::json _body)
{
    std::string body = _body.dump();
    const std::multimap< std::string, std::string > headers
        {
            { "Content-Type", "application/json" },
            { "Content-Length", std::to_string(body.length()) },
            { "Connection", "close" }
        };
    _session->close(_status, body, headers);
}
