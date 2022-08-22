#pragma once

#include "base.h"
#include <boost/asio.hpp>
#include "packet.h"

namespace Bullet
{
class Service : public IBase {
public:
	Service(std::shared_ptr<boost::asio::ip::tcp::socket> sock) : m_sock(sock){}
    void StartHandling();
	void Base() override {}
			
private:
	void onRequestReceived(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void onResponseSent(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void onFinish();

	// std::string ProcessRequest(asio::streambuf& request) {
	Packet ProcessRequest(boost::asio::streambuf& request);

private:
	std::shared_ptr<boost::asio::ip::tcp::socket> m_sock;
	boost::asio::streambuf m_streambuf;
};
}