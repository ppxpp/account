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
	builder.RegisterService(&rpcChannel);
	builder.RegisterService(&pushProxy);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Push Server listening on " << server_address << std::endl;
	server->Wait();
}

void RunAsyncChannelServer() 
{
	std::string server_address(gRPCAddress);
	ServerBuilder builder;
	ChannelPush* pushProxy = new ChannelPush();

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(pushProxy);
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
	t1.join();
	t2.join();
	return 0;
}