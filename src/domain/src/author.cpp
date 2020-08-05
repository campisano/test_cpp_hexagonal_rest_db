#include <domain/author.hpp>

#include <sstream>
#include <stdexcept>

namespace {
    void ensureValidForCreation(const std::string & _name);
    void ensureValidName(const std::string & _name);
}

Author::Author(const std::string & _name)
{
    ensureValidForCreation(_name);
    m_name = _name;
}

Author::~Author()
{
}

const std::string & Author::name() const
{
    return m_name;
}

void Author::name(const std::string & _name)
{
    ensureValidName(_name);
    m_name = _name;
}

namespace {
    void ensureValidForCreation(const std::string & _name)
    {
        ensureValidName(_name);
    }

    void ensureValidName(const std::string & _name)
    {
        std::stringstream msg;

        if (_name.size() == 0) {
            msg << "Name '" << _name << "' is invalid";
            throw std::runtime_error(msg.str());
        }
    }
}
