/*
 * getContacts.cpp
 *
 *  Created on: 26-Jan-2017
 *      Author: navin
 */
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include "getContacts.h"
#include <string>
#include <json.hpp>

using namespace sql;
using json = nlohmann::json;

void Contacts::getContacts(std::string& str , int n)
{
	Driver* driver;
	Connection* con;
	Statement* stmt;
	ResultSet* rs;

	try{
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		con->setSchema("navin");

		stmt = con->createStatement();
		//stmt->setInt(1,n);
		std::string cmd = "select * from Contacts where sno = "+ std::to_string(n);
		rs = stmt->executeQuery(cmd);
		json js;

		while(rs->next())
		{

			js["NAME"] =  rs->getString(2);
		}
		str = js.dump();
	}
	catch (SQLException& e) {
		std::cout <<"1Exception caught  : " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout <<"2Exception caught  : " << std::endl;
	}
	delete rs;
	delete stmt;
	delete con ;
}

