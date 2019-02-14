#include <iostream>
#include <grpcpp/grpcpp.h>

#include "auth.pb.h"
#include "auth.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class AuthClient {
public:
    AuthClient(const std::string & host);
    auth::AuthReply signUp(const std::string userName, const std::string password, const std::string device);
    auth::AuthReply signIn(const std::string userName, const std::string password, const std::string device);
    auth::AuthReply signOut(auth::AuthInfo& authInfo);

private:
  std::unique_ptr<auth::Auth::Stub> stub_;
};