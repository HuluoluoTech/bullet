#include "Log.h"
#include <boost/log/trivial.hpp>

namespace Bullet 
{
// void LOG(const std::string_view message, const std::source_location location = std::source_location::current())
// {
//     std::cout << "File: "
//             << location.file_name() << "("
//             << location.line() << ":"
//             << location.column() << ") `"
//             << location.function_name() << "`: "
//             << message << '\n';
// }
 
void Log::trace(const std::string& log)
{
    BOOST_LOG_TRIVIAL(trace) << log;
}

void Log::debug(const std::string& log)
{
    BOOST_LOG_TRIVIAL(debug) << log;
}

void Log::info(const std::string& log)
{
    BOOST_LOG_TRIVIAL(info) << log;
}

void warning(const std::string& log)
{
    BOOST_LOG_TRIVIAL(warning) << log;
}

void error(const std::string& log)
{
    BOOST_LOG_TRIVIAL(error) << log;
}

void fatal(const std::string& log)
{
    BOOST_LOG_TRIVIAL(fatal) << log;
}

}
