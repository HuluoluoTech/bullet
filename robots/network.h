#include <boost/asio.hpp>
#include <iostream>
#include <packet.h>
#include "bullet.pb.h"

using namespace boost;
using boost::asio::ip::tcp;

class SyncTCPClient {
public:
    SyncTCPClient(const std::string& raw_ip_address, unsigned short port_num) :
    m_ep(asio::ip::address::from_string(raw_ip_address),
    port_num),
    m_sock(m_ios) {
        m_sock.open(m_ep.protocol());
    }

    void connect() {
        m_sock.connect(m_ep);
    }

    void close() {
        m_sock.shutdown(
        boost::asio::ip::tcp::socket::shutdown_both);
        m_sock.close();
    }

    std::string emulateLongComputationOp(unsigned int duration_sec) {
        bullet::Login lg = bullet::Login();
        lg.set_id(222);
        lg.set_playerid("333");
        lg.set_password("password");

        Bullet::Packet packet(1);
        packet.SerializeToBuffer(lg);
        SendPacket(&packet);

        return receiveResponse();
    };

private:
    void sendRequest(const std::string& request) {
        asio::write(m_sock, asio::buffer(request));
    }

    void SendPacket(Bullet::Packet* packet) 
    {
        char* data = packet->GetBuffer();
        size_t size = packet->GetDataLength();
        std::cout << size << std::endl;
        asio::write(m_sock, asio::buffer(data, size));
    }

    std::string receiveResponse() {
        // int size = 0;
        // boost::asio::read(m_sock, boost::asio::buffer(&size, sizeof(uint8_t)));

        asio::streambuf buf;
        asio::read(m_sock, buf, boost::asio::transfer_at_least(1));
 
        boost::asio::streambuf::const_buffers_type cbt = buf.data();
        std::string data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));

        std::cout << "data size: " << data.size() << std::endl;
        
        Bullet::Packet p;
        p.AddBuffer(data.data(), data.size());
        auto lg = p.DeserializeToProto<bullet::Login>();
        std::cout << "p.MsgId   : " << p.GetMsgId() << std::endl;
        std::cout << "p.id      : " << lg.id() << std::endl;
        std::cout << "p.playerdd: " << lg.playerid() << std::endl;
        std::cout << "p.password: " << lg.password() << std::endl;

        return data;
    }

private:
    asio::io_service m_ios;
    asio::ip::tcp::endpoint m_ep;
    asio::ip::tcp::socket m_sock;
};

int run()
{
    const std::string raw_ip_address = "127.0.0.1";
    const unsigned short port_num = 8165;
    try {
        SyncTCPClient client(raw_ip_address, port_num);
        // Sync connect.
        client.connect();

        std::cout << "Sending request to the server... " << std::endl;
        std::string response = client.emulateLongComputationOp(10);
        std::cout << "Response received: " << response << std::endl;
        
        // Close the connection and free resources.
        client.close();
    }
    catch (system::system_error &e) {
        std::cout 
        << "Error occured! Error code = " 
        << e.code()
        << ". Message: " 
        << e.what();

        return e.code().value();
    }

    return 0;
}