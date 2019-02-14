#include <iostream>
#include <string>

#include "transfer/transfer.h"
#include "channel/channel_push.h"
#include "xinge/xinge_push.h"

#include "acl_cpp/lib_acl.hpp"
#include "lib_acl.h"

using namespace std;
using grpc::ClientContext;

const char* CHANNEL_NAME = "push_msg_channel";
const char* MSG_QUEUE_HOST = "docker_redis:6379";

Transfer::Transfer(RedisCache* cache)
{
	this->cache = cache;
}

bool Transfer::xingePush(string device, string msg)
{
	cout << "use xinge psuh to " << device << endl;
	XinGePush::push(device, msg);
	return true;
}

bool Transfer::grpcPush(string host, string device, string msg) {
	std::unique_ptr<push::PushProxy::Stub> stub_ = push::PushProxy::NewStub(grpc::CreateChannel(host, grpc::InsecureChannelCredentials()));
	push::NotifyWrapper wrapper;
	wrapper.set_device(device);
	push::Notify* notify = new push::Notify();
	notify->set_msg(msg);
	wrapper.set_allocated_notify(notify);

	push::Ret ret;
	ClientContext context;
	Status status = stub_->PushToClient(&context, wrapper, &ret);

	// Act upon its status.
	if (status.ok() && ret.err() == 0) {
		cout << "PushToClient complete, " << ret.msg() << endl;
		return true;
	}
	else
	{
		std::cout << "PushToClient failed, " << status.error_code() << ": " << status.error_message() << std::endl;
		return false;
	}
}

void Transfer::pollMsgQueue()
{
	acl::redis_client client(MSG_QUEUE_HOST, 100, 100);
	acl::redis_pubsub redis;
	redis.set_client(&client);
	acl::string channel;
	channel.format("%s", CHANNEL_NAME);
	int ret;
	redis.clear();
	ret = redis.subscribe(channel.c_str(), NULL);
	cout << "init redis client, subscribe ret = " << ret << endl;
	if (ret <= 0)
	{
		printf("subscribe %s error(%s), ret: %d\r\n", channel.c_str(), redis.result_error(), ret);
	}
	else
	{
		printf("subscribe %s ok\r\n", channel.c_str());
	}
	acl::string msg;

	channel.clear();
	msg.clear();
	redis.clear();

	while ((redis.get_message(channel, msg)))
	{
		printf("get one message: %s, channel: %s\r\n", msg.c_str(), channel.c_str());
		string rawMsg(msg.c_str());
		int idx = rawMsg.find_first_of('-', 0);
		//string device = "1234567890";
		string device = rawMsg.substr(0, idx);
		//string pushMsg = "this is msg from transfer";
		string pushMsg = rawMsg.substr(idx + 1, rawMsg.length() - idx - 1);
		cout << "idx = " << idx << ", device = " << device << ", pushMsg = " << pushMsg << endl;
		bool pushOk = false;
		// 判断Cache中是否有device对应的writeStream
		string grpcHost = cache->getValue(device);
		if (!grpcHost.empty())
		{
			cout << "found " << device << " in cache, value is " << grpcHost << endl;
			pushOk = grpcPush(grpcHost, device, pushMsg);
		}
		if(!pushOk)
		{
			pushOk = xingePush(device, pushMsg);
		}
	}
	printf("get_message error(%s)\r\n", redis.result_error());
	msg.clear();
	redis.clear();
}

void Transfer::poll()
{
	pollMsgQueue();
}


void Transfer::develiverNotify(std::string device, std::string msg)
{

}