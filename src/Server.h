#pragma once

// #include <cstdlib>
// #include <iostream>
// #include <utility>
#include <boost/asio.hpp>
#include <thread>
#include <bullet.pb.h>
#include "packet.h"
#include "NetworkMgr.h"
#include "Service.h"

using namespace boost;

namespace Bullet 
{
class Acceptor {
public:
	Acceptor(asio::io_service&ios, unsigned short port_num);
		
	// Start accepting incoming connection requests.
	void Start();

	// Stop accepting incoming connection requests.
	void Stop();

private:
	void InitAccept();
	void onAccept(const boost::system::error_code& ec, std::shared_ptr<asio::ip::tcp::socket> sock);

private:
	asio::io_service& m_ios;
	asio::ip::tcp::acceptor m_acceptor;
	std::atomic<bool> m_isStopped;
};

class Server {
public:
	Server();
	// Start the server.
	void Start(unsigned short port_num, unsigned int thread_pool_size);

	// Stop the server.
	void Stop();

private:
	asio::io_service m_ios;
	std::unique_ptr<asio::io_service::work>m_work;
	std::unique_ptr<Acceptor>acc;
	std::vector<std::unique_ptr<std::thread>>m_thread_pool;
};

} // namespace Bullet


