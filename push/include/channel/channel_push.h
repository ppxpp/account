#pragma once
#include <iostream>
#include <grpcpp/grpcpp.h>

#include "push.grpc.pb.h"
#include "push.pb.h"

using namespace std;

using grpc::Status;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerAsyncReaderWriter;

//extern std::map<string, ServerReaderWriter<push::Notify, push::Cmd>* > streamMap;
extern std::map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>* > AsyncStreamMap;

class ChannelPush: public push::PushProxy::Service {

public:
	Status PushToClient(ServerContext* context, const push::NotifyWrapper* notifyWrapper, push::Ret* ret);

};