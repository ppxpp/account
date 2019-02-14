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

void Push::pushOfflineNotification(std::string deviceToken, std::string userName)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		string accessId ("2100325838");
		std::time_t result = std::time(nullptr);
		std::stringstream strm;
		strm << result;
		string timestamp = strm.str();

		string messageType("2");
		string message= string("{\"title\":\"-\",\"content\":\"-\",\"custom_content\":{\"type\":1,\"user_name\":\"") + userName + "\"}}";
		string raw = string("GETopenapi.xg.qq.com/v2/push/single_device")
			+ "access_id=" + accessId
			+ "device_token=" + deviceToken
			+ "message=" + message
			+ "message_type=" + messageType
			+ "timestamp=" + timestamp
			+ "d98c71fb78c77b9612b8cdbf6393faec";
		cout << "raw = " << endl << raw << endl;
		string sign = Encrypt::md5(raw);
		cout << "sign = " << endl << sign << endl;
		string url = string("http://openapi.xg.qq.com/v2/push/single_device?")
			+ "access_id=" + accessId
			+ "&device_token=" + deviceToken
			+ "&timestamp=" + timestamp
			+ "&message=" + message
			+ "&message_type=" + messageType
			+ "&sign=" + sign;
		cout << "url = " << endl << url << endl;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
		{
			cout << "curl_easy_perform() failed: " << endl << curl_easy_strerror(res) << endl;
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
}