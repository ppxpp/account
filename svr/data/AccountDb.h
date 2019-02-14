#pragma once
#include "../service/AccountService.h"

class AccountDb
{
public:
	int getAccount(std::string userName, Account* account);

	int newAccount(Account* account);

	int setAccountSecret(std::string userName, std::string newSalt, std::string newPwdHash);

	int getToken(std::string userName, int status, Token* token);

	int setTokenStatus(std::string token, int newStatus);

	int newToken(Token* token, std::string userName, int status);
};