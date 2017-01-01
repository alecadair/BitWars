#ifndef MYSQL_H
#define MYSQL_H

#include <string>
#include <vector>

// MySQL C++ connector
#include <driver.h>
#include <mysql_connection.h>
#include <statement.h>

class MySQL {
public:
	MySQL();
	~MySQL();
	int runCommand(std::string command);

private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	std::vector<std::string> getParameters(std::string command);
	bool login(std::string username, std::string password);
	bool addUser(std::string username, std::string password, std::string fullName);
	bool recordProgress();
	bool userExists(std::string username);
};

#endif
