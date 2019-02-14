#include "cache/cache.h"

RedisCache::RedisCache()
{
	this->mClient = new acl::redis_client("docker_redis:6379", 10, 10);
}

string RedisCache::getValue(string _key)
{
	acl::string key;
	key.format("%s", _key.c_str());

	acl::string value;

	acl::redis_string redis;
	redis.set_client(this->mClient);
	redis.clear();
	if (redis.get(key.c_str(), value) == true)
	{
		printf("key: %s, value: %s, len: %d\r\n",
			key.c_str(), value.c_str(),
			(int)value.length());
		return value.c_str();
	}
	else
	{
		printf("get key: %s\r\n", key.c_str());
	}
	return "";
}

int RedisCache::setValue(string _key, string _value)
{
	acl::string key;
	key.format("%s", _key.c_str());

	acl::string value;
	value.format("%s", _value.c_str());

	acl::redis_string redis;
	redis.set_client(this->mClient);
	redis.clear();
	//redis.set_check_addr(false);
	if (redis.set(key.c_str(), value.c_str()) == false)
	{
		printf("set key: %s error: %s\r\n",key.c_str(), redis.result_error());
		return false;
	}
	else
	{
		printf("set key: %s ok\r\n", key.c_str());
	}

	return 0;
}

int RedisCache::deleteKey(string _key)
{
	acl::string key;
	key.format("%s", _key.c_str());

	acl::redis_key redis;
	redis.set_client(this->mClient);
	int ret = redis.del_one(key.c_str());
	printf("deleteKey %s return %d\r\n", key.c_str(), ret);
	return ret;
}