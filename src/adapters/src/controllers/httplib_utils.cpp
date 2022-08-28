#include "httplib_utils.hpp"

#include <string>

void setJSONResponse(
    httplib::Response & _response,
    int _status,
    nlohmann::json _body)
{
    _response.status = _status;
    _response.set_content(_body.dump(), "application/json");
}
