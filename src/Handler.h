#pragma once

#include <string>

namespace Bullet
{
struct Handler
{
    // template <class JsonValue>
    // using Method = std::function <Status (Context&, JsonValue&)>;

    const char* m_name;
};

class HandlerTable
{
public:
    void AddHandler();
    const Handler* GetHandler(std::string const& name) { return new Handler{"Handler"}; }
};

HandlerTable HANDLERS({});

const Handler* GetHandler(std::string const& name) {
    return HANDLERS.GetHandler(name);
}

}