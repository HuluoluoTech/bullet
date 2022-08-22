#include <iostream>
#include <string_view>
#include <source_location>

namespace Bullet
{
    void LOG(const std::string_view message,
            const std::source_location location = 
                std::source_location::current())
    {
        std::cout << "File: "
                << location.file_name() << "("
                << location.line() << ":"
                << location.column() << ") `"
                << location.function_name() << "`: "
                << message << '\n';
    }

    // Define a helper macro to invoke BOOST_ASIO_HANDLER_LOCATION with the current
    // file name, line number, and function name. For the function name, you might
    // also consider using __PRETTY_FUNCTION__, BOOST_CURRENT_FUNCTION, or a hand-
    // crafted name. For C++20 or later, you may also use std::source_location.
    #define HANDLER_LOCATION LOG((__func__))
} // namespace Bullet
    