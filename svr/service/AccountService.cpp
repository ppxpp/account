#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <map>
#include "AccountService.h"
#include "data/AccountDb.h"
#include "utils/Encrypt.h"
#include "utils/Push.h"

// namespace auth
// {

// AccountService::AccountService()
// {

// }
int SignResult::getErr()
{
	return this->mErr;
}

void SignResult::setErr(int err)
{
	this->mErr = err;
}

std::string SignResult::getToken()
{
	return this->mToken;
}

void SignResult::setToken(std::string token)
{
	this->mToken = token;
}

void SignResult::setMsg(std::string msg)
{
	this->mMsg = msg;
}

std::string SignResult::getMsg()
{
	return this->mMsg;
}

// AccountService impl

std::string refreshUserToken(std::string userName, std::string curtDevice)
{
	AccountDb db;
	// find token in used
	Token token;
	int ret = db.getToken(userName, TokenStatus::VALID, &token);
	if (ret == 0)
	{
		// notify this token is expired
		db.setTokenStatus(token.getToken(), TokenStatus::CANCELED);
		std::string device = token.getDevice();
		if (!device.empty() && device.compare(curtDevice) != 0)
		{
			// 发送一个消息出去即可,目前仅仅支持一种消息
			Push::asyncPush(device, userName);
		}
	}
	// create a new token
	token.setToken(Encrypt::genTokenForUser(userName));
	token.setDevice(curtDevice);
	ret = db.newToken(&token, userName, TokenStatus::VALID);
	return ret == 0 ? token.getToken() : "";
}

void AccountService::signUp(std::string userName, std::string password, std::string deivce, SignResult* result)
{
	AccountDb db;
	Account account;
	int ret = db.getAccount(userName, &account);
	if (ret == 0)
	{
		// find a user with this userName
		std::cout << "user already exit" << std::endl;
		result->setErr(ResultCode::USER_EXIT);
	} else if (ret == 1) {
		// insert a new Account
		account.setUserName(userName);
		// create a random salt for this user
		std::string salt = Encrypt::randomSalt();
		account.setSalt(salt);
		// calculate password hash value
		std::string pwdHash = Encrypt::encrypt(password + salt);
		account.setPwdHash(pwdHash);
		account.setDevice(deivce);

		ret = db.newAccount(&account);
		if (ret == 0)
		{
			std::string token = refreshUserToken(userName, deivce);
			if (!token.empty())
			{
				result->setErr(ResultCode::OK);
				result->setToken(token);
				std::cout << "signUp success" << std::endl;
			}
			else
			{
				std::cout << "refresh token error" << std::endl;
				result->setErr(ResultCode::SIGN_UP_ERROR);
			}
		}
		else
		{
			std::cout << "create new Account error" << std::endl;
		}
	}
	else {
		result->setErr(ResultCode::ERROR);
	}
}

void AccountService::signIn(std::string userName, std::string password, std::string device, SignResult* result)
{
	std::cout << "signIn" << std::endl;
	AccountDb db;
	Account account;
	int ret = db.getAccount(userName, &account);
	if (ret == 0)
	{
		// find a user with this userName
		std::string salt = account.getSalt();
		std::string pwdHash = account.getPwdHash();
		// re-calculate password hash
		std::string hash = Encrypt::encrypt(password + salt);
		if (pwdHash.compare(hash) == 0)
		{
			// recreate a new salt for this user and update pwdHash
			// std::string newSalt = Encrypt::randomSalt();
			// std::string newPwdHash = Encrypt::encrypt(password + newSalt);
			// ret = db.setAccountSecret(userName, newSalt, newPwdHash);

			if (ret == 0)
			{
				std::string newToken = refreshUserToken(userName, device);
				if (!newToken.empty())
				{
					result->setErr(ResultCode::OK);
					result->setToken(newToken);
				}
				else
				{
					// error
					std::cout << "refresh token error" << std::endl;
					result->setErr(ResultCode::SIGN_IN_ERROR);
				}
			}
			else
			{
				// error
				std::cout << "update salt error" << std::endl;
				result->setErr(ResultCode::SIGN_IN_ERROR);
				result->setMsg("password error");
			}

		}
		else
		{
			// signIn faild
			std::cout << "password error, pwd in db = " << pwdHash << ", salt in db = " << salt << ", pwd input = " << password << ", pwd cal = " << hash << std::endl;
			result->setErr(ResultCode::USER_NOT_FOUND);
		}
	}
	else if (ret == 1) {
		// user not found
		result->setErr(ResultCode::USER_NOT_FOUND);
	}
	else {
		result->setErr(ResultCode::ERROR);
	}
}

void AccountService::signOut(std::string token, SignResult * result)
{
	std::cout << "signOut, token = " << token << std::endl;
	result->setErr(ResultCode::ERROR);
	if (!token.empty())
	{
		AccountDb db;
		int ret = db.setTokenStatus(token, TokenStatus::EXIPRED);
		if (ret == 0)
		{
			result->setErr(ResultCode::OK);
		}
	}
}
// }