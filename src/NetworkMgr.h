#pragma once

#include "base.h"
#include <map>
#include <boost/asio.hpp>

namespace Bullet
{
using SOCKET = boost::asio::ip::tcp::socket;

class Service;

class NetworkMgr : public IBase
{
public:
    static NetworkMgr& getInstance(){
        static NetworkMgr instance;
        return instance;
    }
private:
    NetworkMgr()  = default;
    ~NetworkMgr() = default;
    NetworkMgr(const NetworkMgr&) = delete;
    NetworkMgr& operator=(const NetworkMgr&) = delete;
    
public:
    void Base() override;

    void AddService(std::shared_ptr<SOCKET> sock, Service* service);
    void EraseService(std::shared_ptr<SOCKET>);
    Service* GetService(std::shared_ptr<SOCKET>);

private:
    // socket <> Service object
    std::map<std::shared_ptr<SOCKET>, Service*> m_services;
};
}