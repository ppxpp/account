#pragma once

class Push
{
public:
	static void pushOfflineNotification(std::string deviceToken, std::string userName);
	static void asyncPush(std::string device, std::string userName);
};