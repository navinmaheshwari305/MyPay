/*
 * Transaction.cpp
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#include <Transaction.h>
#include <statement.h>
#include <DbConnection.h>
namespace myPay
{
Transaction::Transaction()
: sno(0) ,paymentOption(empty) , amount(0)
{
}

Transaction::Transaction(int sno_,PaymentOption po_,double amt_,std::string remarks_,std::string dot_)
: sno(sno_) ,paymentOption(po_) , amount(amt_) , remarks(remarks_), dateOfTransaction(dot_)
{

}

std::string Transaction::toJson()
{
	nlohmann::json poJson = {};
	poJson["sno"] = this->sno;
	poJson["paymentOption"] = PaymentOptionStrArr[this->paymentOption];
	poJson["amount"] = this->amount;
	poJson["remarks"] = this->remarks;
	poJson["dateOfTransaction"] = this->dateOfTransaction;
	return poJson.dump(4);
}
void Transaction::getTrasactionFromJson(std::string& jstr_)
{
	std::cout << "JStr:" << jstr_ << std::endl;
	nlohmann::json js_ = nlohmann::json::parse(jstr_);
	this->sno = js_["sno"] ;
	std::string po = js_["paymentOption"];
	this->paymentOption = getEnumValueForString(po);
	this->amount = js_["amount"] ;
	this->remarks = js_["remarks"];
	this->dateOfTransaction = js_["dateOfTransaction"] ;
}

Transaction::~Transaction() {
	// TODO Auto-generated destructor stub
}

bool Transaction::insertTrasaction()
{
	try{
		sql::Connection *con = DbConnection::getInstance();
		sql::Statement *stmt = con->createStatement();
		std::string query = "Insert into Transaction values ("
				+std::to_string(sno)+",'"+PaymentOptionStrArr[paymentOption]+"','"
				+remarks+"','"+dateOfTransaction+"',"+std::to_string(amount)+")";
		std::cout << " Query:" << query << std::endl;
		if(stmt->executeUpdate(query) == 1 ) return true;
		delete stmt;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
	return false;
}

std::vector<Transaction> Transaction::getTrasaction()
{
	std::vector<Transaction> vec;
	try{
		sql::Connection *con = DbConnection::getInstance();
		sql::Statement *stmt = con->createStatement();
		sql::ResultSet *rs;
		std::string query = "select * from Transaction";
		std::cout << " Query:" << query << std::endl;
		rs = stmt->executeQuery(query);
		while(rs->next())
		{
			Transaction t;
			t.setSno(rs->getInt(1));
			t.setPaymentOption(getEnumValueForString(rs->getString(2)));
			t.setRemarks(rs->getString(3));
			t.setDateOfTransaction(rs->getString(4));
			t.setAmount(rs->getDouble(5));
			vec.push_back(t);
		}
		delete rs;
		delete stmt;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
	return vec;
}

bool Transaction::getTransaction(int sno_)
{
	try{
		sql::Connection *con = DbConnection::getInstance();
		sql::Statement *stmt = con->createStatement();
		sql::ResultSet *rs;
		std::string query = "select * from Transaction where sno = "+std::to_string(sno_);
		std::cout << " Query:" << query << std::endl;
		rs = stmt->executeQuery(query);
		if(rs->next())
		{
			this->setSno(rs->getInt(1));
			this->setPaymentOption(getEnumValueForString(rs->getString(2)));
			this->setRemarks(rs->getString(3));
			this->setDateOfTransaction(rs->getString(4));
			this->setAmount(rs->getDouble(5));
			return true;
		}
		delete rs;
		delete stmt;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
	return false;
}

bool Transaction::deleteTransaction(int sno_)
{
	std::cout << "Delete Transaction" << std::endl;
	try{
		sql::Connection *con = DbConnection::getInstance();
		sql::Statement *stmt = con->createStatement();
		std::string query ("delete from Transaction where sno =" + std::to_string(sno_));
		std::cout << "Sno : "<<sno_<< " Query:" << query << std::endl;
		if (stmt->executeUpdate(query) == 1 )
		{
			return true;
		}
		delete stmt;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
	return false;
}

bool Transaction::updateTransaction()
{
	try{

		sql::Connection *con = DbConnection::getInstance();
		sql::Statement *stmt = con->createStatement();
		std::string query = "UPDATE Transaction SET payment_option = '"+ PaymentOptionStrArr[paymentOption]  + "',remarks ='" + remarks
				+"',	date_of_transaction = '"+dateOfTransaction +"',amount = "+std::to_string(amount) +"WHERE sno = "+std::to_string(sno);
		std::cout << " Query:" << query << std::endl;
		if(stmt->executeUpdate(query) == 1 ) return true;
		delete stmt;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Exception Caught : [ " << __FUNCTION__ << "]["
				<< __LINE__ << "][What:" << e.what() << "]"<< std::endl;
	}
}

};
