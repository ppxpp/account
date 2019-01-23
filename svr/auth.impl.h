#pragma once
#include <grpcpp/grpcpp.h>
#include "auth.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using auth::Auth;
using auth::UserInfo;
using auth::AuthReply;
using auth::AuthInfo;

class AuthImpl final : public auth::Auth::Service {

    Status SignUp(ServerContext* context, 
    const UserInfo* request, AuthReply* response);

    Status SignIn(ServerContext* context, 
    const UserInfo* request, AuthReply* response);

    Status SignOut(ServerContext* context, 
    const AuthInfo* request, AuthReply* response);

};