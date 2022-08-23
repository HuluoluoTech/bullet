#include "Error.h"

namespace Bullet
{
BaseError::BaseError(std::string_view message)
{
    m_message = message;
}
const char* BaseError::what() const noexcept { return m_message.c_str(); }
std::string BaseError::name() const
{
    return "BaseError";
}

///////////
// Terriable Error
const char* TerriableError::what() const noexcept
{
    return BaseError::what();
}
std::string TerriableError::name() const
{
    return "TerriableError";
}

} // namespace Bullet