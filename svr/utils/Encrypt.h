#pragma once
#include <iostream>

class Encrypt
{
public:
	static std::string encrypt(std::string src);

	static std::string randomSalt();

	static std::string genTokenForUser(std::string userName);

	static std::string md5(const std::string input);
};