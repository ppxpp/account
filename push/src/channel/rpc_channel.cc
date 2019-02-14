#include <iostream>
#include "channel/rpc_channel.h"

using namespace std;

RpcChannel::RpcChannel(RedisCache* cache)
{
	this->mCache = cache;
}

Status RpcChannel::Connect(ServerContext* context, ServerReaderWriter<push::Notify, push::Cmd>* stream)
{
	cout << "begin method connect" << endl;
	push::Cmd cmd;
	while (stream->Read(&cmd)) {
		int type = cmd.type();
		string device = cmd.device();
		if (type == 1)
		{
			string device = cmd.device();
			// 判断Cache中是否有device对应的writeStream
			string value = this->mCache->getValue(device);
			if (value.empty())
			{
				cout << "not found " << device << " in cache" << endl;
				this->mCache->setValue(device, gRPCAddress);
				streamMap.insert(pair<string, ServerReaderWriter<push::Notify, push::Cmd>*>(device, stream));
			}
			else 
			{
				cout << "found " << device << " in cache, value is " << value << endl;
			}

			cout << "read cmd from client, type = " << cmd.type() << ", device = " << cmd.device() << endl;

			push::Notify notify;
			notify.set_err(0);
			notify.set_msg("this is msg from server");
			stream->Write(notify);

		}
		else
		{
			cout << "read cmd from client, unknow type = " << cmd.type() << ", device = " << cmd.device() << endl;
		}
	}
	cout << "end method connect" << endl;
	return Status::OK;
}