#pragma once

#include <iostream>

#include "lib_acl.h"
#include "acl_cpp/lib_acl.hpp"

using namespace std;

class RedisCache {
public:
	
	RedisCache();

	string getValue(string key);

	int setValue(string key, string value);

	int deleteKey(string key);

private:
	acl::redis_client* mClient;
};