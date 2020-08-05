#ifndef PERSISTENCE__HPP__
#define PERSISTENCE__HPP__

#include <string>

class Persistence
{
public:
    virtual ~Persistence() = default;

public:
    virtual void init(const std::string & _parameters) = 0;
};

#endif
