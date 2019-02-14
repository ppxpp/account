#include <iostream>
#include <thread>
#include "channel/rpc_channel.h"
#include "channel/channel_push.h"
#include "channel/async_channel.h"
#include "cache/cache.h"
#include "transfer/transfer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

std::string gRPCAddress = "0.0.0.0:50050";
std::map<string, ServerReaderWriter<push::Notify, push::Cmd>* > streamMap;
std::map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>* > AsyncStreamMap;

void RunTransfer()
{
	RedisCache* cache = new RedisCache();
	Transfer transfer(cache);
	transfer.poll();
}

void RunServer() {
	std::string server_address(gRPCAddress);
	RedisCache* cache = new RedisCache();
	RpcChannel rpcChannel(cache);

	ChannelPush pushProxy;

	ServerBuilder builder;
	// todo ʹ��SST����
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&rpcChannel);
	builder.RegisterService(&pushProxy);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Push Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}

void RunAsyncChannelServer() 
{
	std::string server_address(gRPCAddress);
	ServerBuilder builder;
	ChannelPush* pushProxy = new ChannelPush();

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(pushProxy);

	//context_.AsyncNotifyWhenDone(reinterpret_cast<void*>(Type::DONE));
	std::cout << "Server listening on " << server_address << std::endl;

	RedisCache* cache = new RedisCache();
	AsyncRpcChannel* channel = new AsyncRpcChannel(cache, &builder);
}


/**
 * push.cc������Ϣ���У�����Ϣ�󣬽���Ϣ����transfer���зַ���
 * transfer����Ŀ�Ŀͻ����Ƿ������ϣ�ѡ��ʹ��gRPCͨ������ϵͳPush
 */
int main(int argc, char const *argv[])
{
	// ����redis��Ϣ����
	std::cout << "Push Server Running" << std::endl;
	std::thread t1(RunTransfer);
	std::thread t2(RunAsyncChannelServer);
	//RunServer();
	t1.join();
	t2.join();
	//RunAsyncChannelServer();
	return 0;
}