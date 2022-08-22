#pragma once

/**
 * @brief IBase
 * 
 * 所有类都会继承这个基类，以在退出时方便清理资源。
 * 
 */
namespace Bullet 
{
    class IBase
    {
        public:
            virtual ~IBase() = default;
            virtual void Base() = 0;
    };
}