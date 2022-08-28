#ifndef HTTPLIB_UTILS__HPP__
#define HTTPLIB_UTILS__HPP__

#include <json.hpp>
#include <httplib.h>

void setJSONResponse(
    httplib::Response & _response,
    int _status,
    nlohmann::json _body);

#endif
