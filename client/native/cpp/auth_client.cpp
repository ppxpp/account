#include "auth_client.hpp"

AuthClient::AuthClient()
{
    this->stub_ = auth::Auth::NewStub(grpc::CreateChannel("192.168.56.101:50051",
        grpc::InsecureChannelCredentials()));
}

auth::AuthReply AuthClient::signUp(const std::string userName, const std::string password, const std::string device)
{
    auth::UserInfo info;
    info.set_username(userName);
    info.set_pwdhash(password);
	info.set_device(device);

    auth::AuthReply reply;
    ClientContext context;
    Status status = this->stub_->SignUp(&context, info, &reply);

    if (!status.ok()) {
        reply.set_err(1);
        reply.set_msg("failed");
    }
    return reply;
}

auth::AuthReply AuthClient::signIn(const std::string userName, const std::string password, const std::string device)
{
    auth::UserInfo info;
    info.set_username(userName);
    info.set_pwdhash(password);
	info.set_device(device);

    auth::AuthReply reply;
    ClientContext context;
    Status status = this->stub_->SignIn(&context, info, &reply);

    if (!status.ok()) {
        reply.set_err(1);
        reply.set_msg("failed");
    }
    return reply;
}


auth::AuthReply AuthClient::signOut(auth::AuthInfo& authInfo)
{
    auth::AuthReply reply;
    ClientContext context;
    Status status = this->stub_->SignOut(&context, authInfo, &reply);

    if (!status.ok()) {
        reply.set_err(1);
        reply.set_msg("failed");
    }
    return reply;
}