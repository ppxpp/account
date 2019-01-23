#include <iostream>
#include <grpcpp/grpcpp.h>

#include "auth.grpc.pb.h"

#include "auth_client.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using auth::Auth;
using auth::UserInfo;
using auth::AuthReply;
using auth::AuthInfo;


int main(int argc, char const *argv[])
{
    AuthClient client;
    auth::AuthReply reply = client.signUp("ss", "123");
    std::cout<<"signUp: "<< reply.msg() << std::endl;

    reply = client.signIn("ss", "123");
    std::cout<<"signIn: "<< reply.msg() << std::endl;

    auth::AuthInfo authInfo;
    authInfo.set_token("token123");
    reply = client.signOut(authInfo);
    std::cout<<"signOut: "<< reply.msg() << std::endl;

    return 0;
}
