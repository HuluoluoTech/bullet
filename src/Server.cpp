#include "Server.h"
#include <thread>
#include "Log.h"

namespace Bullet
{
Acceptor::Acceptor(boost::asio::io_service&ios, unsigned short port_num) :
m_ios(ios),
m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num)),
m_isStopped(false)
{
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address( true ));
}

void Acceptor::Start() {
    m_acceptor.listen();
    InitAccept();
}

void Acceptor::Stop() {
    m_isStopped.store(true);
}

void Acceptor::InitAccept() {
    std::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(m_ios));
    m_acceptor.async_accept(
        *sock.get(),
        [this, sock](const boost::system::error_code& error)
        {
            onAccept(error, sock);
        });
}

void Acceptor::onAccept(const boost::system::error_code& ec, std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
    if (ec.value() == 0) {
        // Accept A New sock
        Service *service = new Service(sock);
        service->StartHandling();

        NetworkMgr::getInstance().AddService(sock, service);
    }
    else {
        std::cout
            << "Error occured! Error code = "
            << ec.value()
            << ". Message: " << ec.message();
    }

    // Init next async accept operation if
    // acceptor has not been stopped yet.
    if (!m_isStopped.load()) {
        InitAccept();
    }
    else {
    // Stop accepting incoming connections
    // and free allocated resources.
        m_acceptor.close();
    }
}

///////////////////
// Server
Server::Server() {
    m_work.reset(new boost::asio::io_service::work(m_ios));
}

void Server::Start(unsigned short port_num, unsigned int thread_pool_size) {
    assert(thread_pool_size > 0);

    Log::debug("Server starting...");

    // Create and start Acceptor.
    acc.reset(new Acceptor(m_ios, port_num));
    acc->Start();

    // Create specified number of threads and
    // add them to the pool.
    for (unsigned int i = 0; i < thread_pool_size; i++) {
        std::unique_ptr<std::thread> th(
            new std::thread([this]()
            {
                m_ios.run();
            })
        );
        
        // It blocks the current thread until the execution of the thread is completed on which join() is called.
        // Segmentation fault (core dumped)
        th->join();

        m_thread_pool.push_back(std::move(th));
    }
}

void Server::Stop() {
    acc->Stop();
    m_ios.stop();

    // for (auto& th : m_thread_pool) {
    // 	th->join();
    // }
}

}