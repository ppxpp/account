#include <iostream>
#include "auth.impl.h"

#include "utils/Push.h"

#include "lib_acl.h"
#include "acl_cpp/lib_acl.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

static acl::string __keypre("test_key");

static bool test_del(acl::redis_key& redis, int n)
{
	acl::string key;

	for (int i = 0; i < n; i++)
	{
		key.format("%s_%d", __keypre.c_str(), i);
		redis.clear();
		int ret = redis.del_one(key.c_str());
		if (ret < 0)
		{
			printf("del key: %s error: %s\r\n",
				key.c_str(), redis.result_error());
			return false;
		}
		else if (i < 10)
			printf("del ok, key: %s, ret: %d\r\n", key.c_str(), ret);
	}

	return true;
}

void redis() {
	acl::redis_client client("127.0.0.1:6379", 10, 10);
	acl::redis_key redis;
	redis.set_client(&client);
	
	test_del(redis, 4);
}

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  AuthImpl service;

  ServerBuilder builder;
  // todo 使用SST连接
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char const *argv[])
{
    std::cout<<"hello"<<std::endl;
    RunServer();
	// redis();
	//Push::pushOfflineNotification("ca05f5083bb12ec74598be26793e09396de0beab", "alice");
    return 0;
}
