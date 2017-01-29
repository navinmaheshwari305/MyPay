/*
 * DbConnection.h
 *
 *  Created on: 29-Jan-2017
 *      Author: navin
 */

#ifndef DB_DBCONNECTION_H_
#define DB_DBCONNECTION_H_

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>

namespace myPay {

class DbConnection {
private:
	bool closeCon();
	sql::Driver* driver;;
	sql::Connection* connection;
	DbConnection();
public:
	void setDbConnection(const std::string& schema ,
				const std::string& username , const std::string& password);
	static myPay::DbConnection* dbCon;
	bool isClosed();
	static bool init_database(const std::string& schema , const std::string& username , const std::string& password);
	static sql::Connection* getInstance();

	virtual ~DbConnection();
};

} /* namespace myPay */

#endif /* DB_DBCONNECTION_H_ */
