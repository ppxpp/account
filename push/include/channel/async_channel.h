#pragma once
#include <iostream>
#include <thread>
#include <grpcpp/grpcpp.h>

#include "cache/cache.h"
#include "push.grpc.pb.h"
#include "push.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::Status;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::ServerAsyncReaderWriter;

extern std::string gRPCAddress;
//extern std::map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>* > streamMap;
extern std::map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>* > AsyncStreamMap;

class AsyncRpcChannel {
public:
	AsyncRpcChannel(RedisCache* cache, ServerBuilder* serverBuilder);

	~AsyncRpcChannel();

private:

	class CallData {
	public:
		CallData(RedisCache* cache, push::PushChannel::AsyncService* service, ServerCompletionQueue* cq);
		void Proceed();

	private:
		enum CallStatus { CREATE, CONNECT, PROCESS, FINISH };
		CallStatus status_;

		std::string device;
		RedisCache* cache_;
		ServerContext ctx_;
		push::PushChannel::AsyncService* service_;
		ServerCompletionQueue* cq_;

		push::Cmd cmd_;
		std::unique_ptr<ServerAsyncReaderWriter<push::Notify, push::Cmd>> stream_;
	};

	void HandleRpcs();

	RedisCache* mCache;
	ServerContext context_;
	std::unique_ptr<ServerCompletionQueue> cq_;
	std::unique_ptr<Server> server_;
	push::PushChannel::AsyncService service_;
	//std::unique_ptr<std::thread> grpc_thread_;
};