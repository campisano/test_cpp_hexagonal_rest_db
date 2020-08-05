#ifndef AUTHOR__HPP__
#define AUTHOR__HPP__

#include <string>

class Author
{
public:
    explicit Author(
        const std::string & _name);
    Author(const Author &) = delete;
    Author(Author &&) = default;
    virtual ~Author();

    Author & operator=(const Author &) = delete;
    Author & operator=(Author &&) = default;

public:
    const std::string & name() const;
    void name(const std::string & _name);

private:
    std::string m_name;
};

#endif
