#pragma once
#include <iostream>
#include "channel/async_channel.h"

extern std::map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>* > AsyncStreamMap;

/**
 * 内部根据指定客户端的在离线情况，选择一个下发通道
 */
class Transfer {
public:
	Transfer(RedisCache* cache);
	void poll();
	static void develiverNotify(std::string device, std::string msg);
private:
	bool grpcPush(string host, string device, string msg);
	bool xingePush(string device, string msg);
	void pollMsgQueue();

	RedisCache* cache;
};