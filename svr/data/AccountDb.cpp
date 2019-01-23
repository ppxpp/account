#include "AccountDb.h"
#include "AccountDb.h"
#include "AccountDb.h"
#include "AccountDb.h"
#include "AccountDb.h"
#include "AccountDb.h"

#include "driver.h"
#include "prepared_statement.h"

int AccountDb::getAccount(std::string userName, Account * account)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("SELECT `user_name`, `pwd_hash`, `salt` from tbl_user where `user_name`=?");
		stmt->setString(1, userName);

		res = stmt->executeQuery();
		int rowCount = res->rowsCount();
		std::cout << "getAccount, query count = " << rowCount << std::endl;
		
		if (rowCount == 1)
		{
			res->next();
			ret = 0;
			account->setUserName(res->getString(1));
			account->setPwdHash(res->getString(2));
			account->setSalt(res->getString(3));
		}
		else {
			ret = 1;
		}
		delete res;
		delete stmt;
		delete con;
	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}

int AccountDb::newAccount(Account* account)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("insert into `tbl_user`(`user_name`, `pwd_hash`, `salt`) values (?, ?, ?, ?)");
		stmt->setString(1, account->getUserName());
		stmt->setString(2, account->getPwdHash());
		stmt->setString(3, account->getSalt());

		int rowCount = stmt->executeUpdate();
		std::cout << "newAccount, executeUpdate rowCount = " << rowCount << std::endl;
		ret = rowCount == 1 ? 0 : 1;

		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}

int AccountDb::setAccountSecret(std::string userName, std::string newSalt, std::string newPwdHash)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("update `tbl_user` set `salt`=?, `pwd_hash`=? where `user_name`=?");
		stmt->setString(1, newSalt);
		stmt->setString(2, newPwdHash);
		stmt->setString(3, userName);

		int rowCount = stmt->executeUpdate();
		std::cout << "setAccountSecret, executeUpdate rowCount = " << rowCount << std::endl;
		ret = rowCount == 1 ? 0 : 1;

		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}

int AccountDb::getToken(std::string userName, int status, Token* token)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::ResultSet *res;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("SELECT `token`, `device` from tbl_token where `user_name`=? and `status`=?");
		stmt->setString(1, userName);
		stmt->setInt(2, status);

		res = stmt->executeQuery();
		int rowCount = res->rowsCount();
		std::cout << "getToken, query ccunt = " << rowCount << std::endl;

		if (rowCount == 1)
		{
			ret = 0;
			res->next();
			token->setToken(res->getString(1));
			token->setDevice(res->getString(2));
		}
		else
		{
			ret = 1;
		}
		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}

int AccountDb::setTokenStatus(std::string token, int newStatus)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("update `tbl_token` set `status`=? where `token`=?");
		stmt->setInt(1, newStatus);
		stmt->setString(2, token);

		int rowCount = stmt->executeUpdate();
		std::cout << "setTokenStatus, executeUpdate rowCount = " << rowCount << std::endl;
		ret = 0;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}

int AccountDb::newToken(Token* token, std::string userName, int status)
{
	int ret = -1;
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement* stmt;
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		/* Connect to the MySQL test database */
		con->setSchema("account");
		stmt = con->prepareStatement("insert into `tbl_token`(`user_name`, `token`, `status`, `device`) values (?, ?, ?, ?)");
		stmt->setString(1, userName);
		stmt->setString(2, token->getToken());
		stmt->setInt(3, status);
		stmt->setString(4, token->getDevice());

		int rowCount = stmt->executeUpdate();
		std::cout << "newToken, executeUpdate rowCount = " << rowCount << std::endl;
		ret = rowCount == 1 ? 0 : 1;

		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	return ret;
}
