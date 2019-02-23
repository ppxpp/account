#include <iostream>
#include "auth.impl.h"

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
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char const *argv[])
{
    RunServer();
    return 0;
}
