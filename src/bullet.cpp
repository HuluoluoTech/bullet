#include <bullet.h>
#include <iostream>
#include <login.pb.h>

void test()
{
    google::protobuf::ShutdownProtobufLibrary();	//删除所有已分配的内存（Protobuf使用的堆内存）
}