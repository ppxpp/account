#pragma once
#include <iostream>
#include <grpcpp/grpcpp.h>

#include "cache/cache.h"
#include "push.grpc.pb.h"
#include "push.pb.h"

using grpc::Status;
using grpc::ServerContext;
using grpc::ServerReaderWriter;

extern std::string gRPCAddress;
extern std::map<string, ServerReaderWriter<push::Notify, push::Cmd>* > streamMap;

class RpcChannel : public push::PushChannel::Service {
public:

	RpcChannel(RedisCache* cache);

	Status Connect(ServerContext* context, ServerReaderWriter<push::Notify, push::Cmd>* stream);

private:
	RedisCache* mCache;
};