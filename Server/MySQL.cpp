#include "MySQL.h"
#include <string>
#include <vector>
#include <iostream>

// MySQL C++ connector
#include <driver.h>
#include <mysql_connection.h>
#include <statement.h>
#include <exception.h>
#include <resultset.h>

MySQL::MySQL() {

}

MySQL::~MySQL() {
	// Close and free MySQL objects
	stmt->close();
  con->close();
  delete stmt;
  delete con;
  driver->threadEnd();
}

// Returns 0/1 if result was false/true
// Returns 2 if there was an SQL error
int MySQL::runCommand(std::string command) {
	try {
		// Connect to AWS MySQL database
		driver = get_driver_instance();
		con = driver->connect("cs3505.cpne1wf1lnry.us-west-2.rds.amazonaws.com:3505", "admin", "scrumandcoke");
		con->setSchema("cs3505");
		stmt = con->createStatement();

		std::vector<std::string> parameters = getParameters(command);

		if (command.find("LOGIN") == 0) {
			return login(parameters.at(0), parameters.at(1));
		}
		else if (command.find("ADUSR") == 0) {
			return addUser(parameters.at(0), parameters.at(1), parameters.at(2));
		}
		else if (command.find("RPROG") == 0) {
			return recordProgress();
		}
		else if (command.find("USREX") == 0) {
			return userExists(parameters.at(0));
		}
	}
	catch (sql::SQLException &e) {
		std::cout << e.what() << std::endl;
	}
	
	return 2;
}

std::vector<std::string> MySQL::getParameters(std::string command) {
	std::vector<std::string> parameters;

	// Remove command portion and ending '$'
	command.erase(0, 6);
	command.erase(command.length() - 1, 1);

	// Add parameters
	size_t position;
	while (command.length() > 0) {
		position = command.find(",");
		if (position == std::string::npos) {
			// Last parameter
			parameters.push_back(command);
			command = "";
		}
		else {
			// Other parameters
			parameters.push_back(command.substr(0, position));
			command.erase(0, position + 1);
		}
	}

	return parameters;
}

bool MySQL::login(std::string username, std::string password) {
	sql::ResultSet *res;
	res = stmt->executeQuery("SELECT COUNT(*) ct FROM User WHERE login='"+username+"' AND password='"+password+"'");
	res->next();
	int result = res->getInt("ct");

	// Close and free result set
	res->close();
	delete res;

	return result;
}

bool MySQL::addUser(std::string username, std::string password, std::string fullName) {
	stmt->execute("INSERT INTO User VALUES ('"+username+"','"+password+"','"+fullName+"')");
	return 1;
}

bool MySQL::recordProgress() {
	// To be implemented
	return 2;
}

bool MySQL::userExists(std::string username) {
	sql::ResultSet *res;
	res = stmt->executeQuery("SELECT COUNT(*) ct FROM User WHERE login='"+username+"'");
	res->next();
	int result = res->getInt("ct");

	// Close and free result set
	res->close();
	delete res;

	return result;
}
