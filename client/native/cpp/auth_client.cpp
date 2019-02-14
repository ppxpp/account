#include "auth_client.hpp"

AuthClient::AuthClient(const std::string & host)
{
    this->stub_ = auth::Auth::NewStub(grpc::CreateChannel(host, grpc::InsecureChannelCredentials()));
}

auth::AuthReply AuthClient::signUp(const std::string userName, const std::string password, const std::string device)
{
    // todo 增加密码加密逻辑
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
     // todo 增加密码加密逻辑
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
