#include "NetworkMgr.h"
#include "Service.h"

namespace Bullet
{
void NetworkMgr::Base() {}
void NetworkMgr::AddService(std::shared_ptr<SOCKET> sock, Service* service)
{
    m_services.emplace(sock, service);
}
void NetworkMgr::EraseService(std::shared_ptr<SOCKET> sock)
{
    m_services.erase(sock);
}
Service* NetworkMgr::GetService(std::shared_ptr<SOCKET> sock)
{
    auto iter = m_services.find(sock);
    if (iter == m_services.end()) 
    {
        std::cout << "Not Found service..." << std::endl;

        return nullptr;
    }

    return iter->second;
}

} // namespace Bullet