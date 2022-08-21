//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "log.h"
#include <thread>

using namespace boost;

namespace Bullet 
{
class Service {
public:
	Service(std::shared_ptr<asio::ip::tcp::socket> sock) :
	m_sock(sock)
	{}

	void StartHandling() {
		asio::async_read_until(*m_sock.get(),
		m_request,
		'\n',
		[this](
		const boost::system::error_code& ec,
		std::size_t bytes_transferred)
		{
			onRequestReceived(ec,
			bytes_transferred);
		});
	}
			
private:
	void onRequestReceived(const boost::system::error_code& ec,
	std::size_t bytes_transferred) {
		if (ec) {
			std::cout << "Error occured! Error code = "
			<< ec.value()
			<< ". Message: " << ec.message();
			onFinish();
			return;
		
		}

		// Process the request.
		m_response = ProcessRequest(m_request);
		// Initiate asynchronous write operation.
		asio::async_write(*m_sock.get(),
		asio::buffer(m_response),
		[this](
		const boost::system::error_code& ec,
		std::size_t bytes_transferred)
		{
		onResponseSent(ec,
		bytes_transferred);
		});
	}

	void onResponseSent(const boost::system::error_code& ec, std::size_t bytes_transferred) {
		if (ec) {
		std::cout << "Error occured! Error code = "
		<< ec.value()
		<< ". Message: " << ec.message();
		}

		onFinish();
	}

	// Here we perform the cleanup.
	void onFinish() {
		delete this;
	}

	std::string ProcessRequest(asio::streambuf& request) {
		// In this method we parse the request, process it
		// and prepare the request.
		// Emulate CPU-consuming operations.
		int i = 0;
		while (i != 1000000)
			i++;

		// Emulate operations that block the thread
		// (e.g. synch I/O operations).
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// Prepare and return the response message.
		std::string response = "HI, Response\n";
		return response;
	}

private:
	std::shared_ptr<asio::ip::tcp::socket> m_sock;
	std::string m_response;
	asio::streambuf m_request;
};

class Acceptor {
public:
	Acceptor(asio::io_service&ios, unsigned short port_num) :
	m_ios(ios),
	m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port_num)),
	m_isStopped(false)
	{}
		
	// Start accepting incoming connection requests.
	void Start() {
		m_acceptor.listen();
		InitAccept();
	}

	// Stop accepting incoming connection requests.
	void Stop() {
		m_isStopped.store(true);
	}

private:
	void InitAccept() {
	std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(m_ios));
	m_acceptor.async_accept(
		*sock.get(),
		[this, sock](const boost::system::error_code& error)
		{
			onAccept(error, sock);
		});
	}

	void onAccept(const boost::system::error_code&ec, std::shared_ptr<asio::ip::tcp::socket> sock)
	{
		if (ec.value() == 0) {
			(new Service(sock))->StartHandling();
		}
		else {
			std::cout
			<< "Error occured! Error code = "
			<< ec.value()
			<< ". Message: " <<ec.message();
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

private:
	asio::io_service&m_ios;
	asio::ip::tcp::acceptor m_acceptor;
	std::atomic<bool> m_isStopped;
};

class Server {
public:
	Server() {
		m_work.reset(new asio::io_service::work(m_ios));
	}

	// Start the server.
	void Start(unsigned short port_num, unsigned int thread_pool_size) {
		HANDLER_LOCATION;

		assert(thread_pool_size > 0);
		// Create and start Acceptor.
		acc.reset(new Acceptor(m_ios, port_num));
		acc->Start();
		m_ios.run();

		// Create specified number of threads and
		// add them to the pool.
		// for (unsigned int i = 0; i < thread_pool_size; i++) {
		// 	std::unique_ptr<std::thread> th(
		// 	new std::thread([this]()
		// 	{
		// 		m_ios.run();
		// 	}));
			
		// 	m_thread_pool.push_back(std::move(th));

		// 	th->join();
		// }
	}
		
	// Stop the server.
	void Stop() {
		acc->Stop();
		m_ios.stop();

		for (auto& th : m_thread_pool) {
			th->join();
		}
	}

private:
	asio::io_service m_ios;
	std::unique_ptr<asio::io_service::work>m_work;
	std::unique_ptr<Acceptor>acc;
	std::vector<std::unique_ptr<std::thread>>m_thread_pool;
};

} // namespace Bullet


