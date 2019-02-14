#include "auth.impl.h"
#include "service/AccountService.h"

Status AuthImpl::SignUp(ServerContext* context, 
        const UserInfo* request, AuthReply* response) 
{
	std::cout << "AuthImpl::SignUp" << std::endl;
    AccountService actSvr;
	SignResult result;
    actSvr.signUp(request->username(), request->pwdhash(), request->device(), &result);
	response->set_err(result.getErr());
	response->set_msg(result.getMsg());
	if (result.getErr() == 0)
	{
		AuthInfo* info = new AuthInfo();
		info->set_token(result.getToken());
		response->set_allocated_data(info);
	}
	return Status::OK;
}

Status  AuthImpl::SignIn(ServerContext* context, 
    const UserInfo* request, AuthReply* response) 
{
	std::cout << "AuthImpl::SignIn" << std::endl;
	AccountService actSvr;
	SignResult result;
	actSvr.signIn(request->username(), request->pwdhash(), request->device(), &result);
	response->set_err(result.getErr());
	response->set_msg(result.getMsg());
	if (result.getErr() == 0)
	{
		AuthInfo* info = new AuthInfo();
		info->set_token(result.getToken());
		response->set_allocated_data(info);
	}
    return Status::OK;
}

Status  AuthImpl::SignOut(ServerContext* context, 
    const AuthInfo* request, AuthReply* response) 
{
	std::cout << "AuthImpl::SignOut" << std::endl;
	AccountService actSvr;
	SignResult result;
	actSvr.signOut(request->token(), &result);
	response->set_err(result.getErr());
	response->set_msg(result.getMsg());
	return Status::OK;
}