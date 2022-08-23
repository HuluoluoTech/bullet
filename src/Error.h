#pragma once

// #include <boost/system/error_code.hpp>
#include "base.h"
#include <string_view>
#include <string>
#include <iostream>

namespace Bullet 
{
/**
 * @brief Error Base Class
 * 
 *  try
 *  {
 *      // Throw by Value
 *      throw BaseError(error_code);
 *  } 
 *  catch (const BaseError& be) // Catch by Reference
 *  {
 *      std::cout << typeid(t).name() << " object caught: " << t.what() << std::endl;
 *  }
 * 
 */
class BaseError : public IBase, std::exception
{
public:
    explicit BaseError(std::string_view message = "There's a problem");
    void Base() {}

    const char* what() const noexcept override;
    virtual std::string name() const;

private:
    std::string m_message;
};

class TerriableError : public BaseError
{
public:
    const char* what() const noexcept override;
    std::string name() const override;
};
}