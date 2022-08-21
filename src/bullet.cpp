#include "bullet.h"
#include <iostream>
#include <login.pb.h>
#include "server.h"
#include "config.h"

void test()
{
    google::protobuf::ShutdownProtobufLibrary();	//删除所有已分配的内存（Protobuf使用的堆内存）
}

namespace Bullet
{
    void Bullet::Start()
    {
        HANDLER_LOCATION;

        unsigned short port_num = Config::PORT;
        try {
            Server srv;
            unsigned int thread_pool_size = std::thread::hardware_concurrency() * 2;
            if (thread_pool_size == 0)
                thread_pool_size = Config::DEFAULT_THREAD_POOL_SIZE;

            srv.Start(port_num, thread_pool_size);

            // std::this_thread::sleep_for(std::chrono::seconds(60));

            // srv.Stop();
        }
        catch (system::system_error&e) {
            std::cout << "Error occured! Error code = "
            <<e.code() << ". Message: "
            <<e.what();
        }

    }
}