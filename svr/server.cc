#include <iostream>
#include "auth.impl.h"

#include "utils/Push.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

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

	//Push::pushOfflineNotification("ca05f5083bb12ec74598be26793e09396de0beab", "alice");
    return 0;
}
