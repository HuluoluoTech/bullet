#pragma once

#include <string>
// https://www.boost.org/doc/libs/1_79_0/libs/log/doc/html/log/tutorial.html#log.tutorial.trivial

namespace Bullet
{
class Log
{
// public:
//     static Log& getInstance(){
//         static Log instance;
//         return instance;
//     }
// private:
//     Log()  = default;
//     ~Log() = default;
//     Log(const Log&) = delete;
//     Log& operator=(const Log&) = delete;

public:
    static void trace  (const std::string& log);
    static void debug  (const std::string& log);
    static void info   (const std::string& log);
    static void warning(const std::string& log);
    static void error  (const std::string& log);
    static void fatal  (const std::string& log);
};
    // void LOG(const std::string_view message, const std::source_location location = std::source_location::current());

    // // Define a helper macro to invoke BOOST_ASIO_HANDLER_LOCATION with the current
    // // file name, line number, and function name. For the function name, you might
    // // also consider using __PRETTY_FUNCTION__, BOOST_CURRENT_FUNCTION, or a hand-
    // // crafted name. For C++20 or later, you may also use std::source_location.
    // #define HANDLER_LOCATION LOG((__func__))
} // namespace Bullet
    