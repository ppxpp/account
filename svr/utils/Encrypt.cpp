#include <algorithm> 
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include "Encrypt.h"
#include "md5.h"


std::string sha256(const std::string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	return ss.str();
}

std::string Encrypt::encrypt(std::string src)
{
	return sha256(src);
}

std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

std::string Encrypt::randomSalt()
{
	// // todo 使用安全的随机数方法
	return random_string(8);
}

std::string Encrypt::genTokenForUser(std::string userName)
{
	return random_string(32);
}

std::string Encrypt::md5(const std::string input)
{
	return MD5(input).toStr();
}
