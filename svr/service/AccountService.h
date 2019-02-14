#pragma once
#include <iostream>

// namespace auth{

class Account
{
public:
	void setUserName(std::string userName) { this->mUserName = userName; }
	std::string getUserName() { return this->mUserName; }

	void setSalt(std::string salt) { this->mSalt = salt; }
	std::string getSalt() { return this->mSalt; }

	void setPwdHash(std::string pwdHash) { this->mPwdHash = pwdHash; }
	std::string getPwdHash() { return this->mPwdHash; }

	void setDevice(std::string device) { this->mDevice = device; };
	std::string getDevice() { return this->mDevice; }

private:
	std::string mUserName;
	std::string mSalt;
	std::string mPwdHash;
	std::string mDevice;

};

enum ResultCode {
	ERROR = -1,
	OK = 0,
	USER_EXIT = 1,
	USER_NOT_FOUND = 3,
	SIGN_IN_ERROR = 4,
	SIGN_UP_ERROR = 5,
	OTHER = 20
};

enum TokenStatus {
	VALID = 1,
	EXIPRED = 2, // 退出登录，使之失效
	CANCELED = 3	 // 被新的登录操作剔除
};

class Token
{
public:

	void setToken(std::string token) { this->mToken = token; };
	std::string getToken() { return this->mToken; }


	void setDevice(std::string device) { this->mDevice = device; };
	std::string getDevice() { return this->mDevice; }

private:
	std::string mToken;
	std::string mDevice;
};

class SignResult
{
public:
    int getErr();
    void setErr(int err);

	std::string getToken();
	void setToken(std::string token);

	void setMsg(std::string msg);
	std::string getMsg();

private:
	std::string mToken;
    int mErr;
	std::string mMsg;
};

class AccountService
{
public:
	void signUp(std::string userName, std::string password, std::string deivce, SignResult* result);

	void signIn(std::string userName, std::string password, std::string deivce, SignResult* result);

	void signOut(std::string token, SignResult* result);

private:
};

// }