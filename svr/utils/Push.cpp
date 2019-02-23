#include "curl/curl.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "Push.h"
#include "Encrypt.h"

#include "lib_acl.h"
#include "acl_cpp/lib_acl.hpp"

using namespace std;


const char* CHANNEL_NAME = "push_msg_channel";
const char* MSG_QUEUE_HOST = "docker_redis:6379";

void Push::asyncPush(std::string device, std::string userName)
{
	acl::redis_client client(MSG_QUEUE_HOST, 100, 100);
	acl::redis_pubsub redis;
	redis.set_client(&client);
	cout << "init redis client, device = " << device << ", userName = " << userName << endl;
	acl::string channel, msg;
	channel.format("%s", CHANNEL_NAME);
	std::string pushMsg = string("{\"title\":\"-\",\"content\":\"-\",\"custom_content\":{\"type\":1,\"user_name\":\"") + userName + "\"}}";;
	msg.format("%s-%s", device.c_str(), pushMsg.c_str());
	int ret = redis.publish(channel.c_str(), msg.c_str(), msg.length());
	if (ret <= 0)
	{
		printf("publish to %s %s error(%s), ret: %d\r\n",
			channel.c_str(), msg.c_str(),
			redis.result_error(), ret);
	}
	else 
	{
		printf("publish to %s %s ok\r\n", channel.c_str(),
			msg.c_str());
	}
}
