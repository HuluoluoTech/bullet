#pragma once

#include <string>

namespace Bullet
{
struct Handler
{
    // template <class JsonValue>
    // using Method = std::function <Status (Context&, JsonValue&)>;

    const char* name_;
};

class HandlerTable
{
public:
    void AddHandler();
    const Handler* GetHandler(std::string const& name);
};

HandlerTable HANDLERS({});

const Handler* getHandler(std::string const& name) {
    return HANDLERS.GetHandler(name);
}

}