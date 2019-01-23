#include "auth_impl.hpp"
#include "auth_reply.hpp"
#include "user_info.hpp"
#include "auth_info.hpp"


namespace act {

AuthImpl::AuthImpl() {
	mClient = new AuthClient();
}

std::shared_ptr<act::Auth> act::Auth::create()
{
	return std::make_shared<AuthImpl>();
}

AuthReply AuthImpl::sign_up(const act::UserInfo & user)
{
	auth::AuthReply _reply = mClient->signUp(user.user_name, user.pwd_hash, user.device);
	auth::AuthInfo _info = _reply.data();
	AuthInfo info(_info.token());
	AuthReply reply(_reply.err(), _reply.msg(), info);
	return reply;
}

AuthReply act::AuthImpl::sign_in(const act::UserInfo & user)
{
	auth::AuthReply _reply = mClient->signIn(user.user_name, user.pwd_hash, user.device);
	auth::AuthInfo _info = _reply.data();
	AuthInfo info(_info.token());
	AuthReply reply(_reply.err(), _reply.msg(), info);
	return reply;
}


AuthReply act::AuthImpl::sign_out(const act::AuthInfo & auth)
{
	auth::AuthInfo _authInfo;
	_authInfo.set_token(auth.token);
	auth::AuthReply _reply = mClient->signOut(_authInfo);
	AuthInfo info("");
	AuthReply reply(_reply.err(), _reply.msg(), info);
	return reply;
}

int32_t act::AuthImpl::update(const UserInfo & user)
{
	return 0;
}

}