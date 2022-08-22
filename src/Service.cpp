#include "Service.h"
#include "bullet.pb.h"

namespace Bullet
{
void Service::StartHandling() {
    boost::asio::async_read(*m_sock.get(), m_streambuf, boost::asio::transfer_at_least(1),  
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred)
        {
            std::cout << "bytes_transferred: " << bytes_transferred << std::endl;
            onRequestReceived(ec, bytes_transferred);
        }
    );
}

void Service::onRequestReceived(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    // Process the request.
    auto p = ProcessRequest(m_streambuf);

    // Initiate asynchronous write operation.
    size_t size = p.GetDataLength();		
    // size_t size = m_response.size();		
    // asio::async_write(*m_sock.get(), asio::buffer(m_response, size),
    boost::asio::async_write(*m_sock.get(), boost::asio::buffer(p.GetBuffer(), size),
        [this](
        const boost::system::error_code& ec, std::size_t bytes_transferred)
        {
            onResponseSent(ec, bytes_transferred);
        }
    );
}

void Service::onResponseSent(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (ec) {
        std::cout 
        << "Error occured! Error code = "
        << ec.value()
        << ". Message: " << ec.message();
    }

    // onFinish();
}

// Here we perform the cleanup.
void Service::onFinish() {
    delete this;
}

Packet Service::ProcessRequest(boost::asio::streambuf& request) {
    // // In this method we parse the request, process it
    // // and prepare the request.
    // // Emulate CPU-consuming operations.
    // int i = 0;
    // while (i != 1000000)
    // 	i++;

    // // Emulate operations that block the thread
    // // (e.g. synch I/O operations).
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    boost::asio::streambuf::const_buffers_type cbt = request.data();
    std::string data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
    std::cout << data.size() << std::endl;

    Packet p;
    p.AddBuffer(data.c_str(), data.size());
    auto pp = p.DeserializeToProto<bullet::Login>();
    p.SerializeToBuffer(pp);
    std::cout << pp.id() << std::endl;
    std::cout << pp.playerid() << std::endl;
    std::cout << pp.password() << std::endl;

    return p;
    // return std::string(p.GetBuffer(), data.size());
    // Prepare and return the response message.
}

} // namespace Bullet