/*
 * DbConnection.cpp
 *
 *  Created on: 29-Jan-2017
 *      Author: navin
 */

#include <iostream>
#include "DbConnection.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
using namespace sql;

namespace myPay {

DbConnection* DbConnection::dbCon = nullptr;

DbConnection::DbConnection()
{}

void DbConnection::setDbConnection(const std::string& schema ,
		const std::string username , const std::string password) {

	try{
		driver = get_driver_instance();
		connection = driver->connect("tcp://127.0.0.1:3306" , username , password);
		connection->setSchema(schema);
	}
	catch (SQLException e) {
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
}

DbConnection::~DbConnection() {
	closeCon();
}

bool DbConnection::init_database(const std::string& schema , const std::string username , const std::string password)
{
	dbCon = new DbConnection();
	dbCon->setDbConnection(schema,username,password);
}
bool DbConnection::isClosed()
{
	if(!connection->isClosed() && connection->isValid()) return false;
	return true;
}

bool DbConnection::closeCon()
{
	connection->close();
	delete connection;
}

sql::Connection* DbConnection::getInstance()
{
	if( dbCon->isClosed())
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What: DB closed now, Kal AANA]"<< std::endl;
	}
	return dbCon->connection;
}

} /* namespace myPay */
