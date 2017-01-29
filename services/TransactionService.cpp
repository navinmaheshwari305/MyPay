/*
 * TransactionService.cpp
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#include "TransactionService.h"
#include "../utils/MyPayUtils.h"

namespace myPay
{

TransactionService::TransactionService()
{
	// TODO Auto-generated constructor stub

}

TransactionService::~TransactionService()
{
	// TODO Auto-generated destructor stub
}

void TransactionService::get_Transaction_controller(const shared_ptr< Session > session)
{

	const auto& request = session->get_request();
	size_t content_length = request->get_header( "Content-Length", 0 );
	session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
			{
		std::string ret;
		if(request->has_query_parameter("sno"))
		{
//			const char* c = reinterpret_cast<const char*>(body.data());
//			std::string str =std::string(c);
//			removeJunkChars(str);
//			nlohmann::json js  = nlohmann::json::parse(str);
//			std::cout << " Substd::string ---| " << str << "|---" << std::endl;
//			int sno = js["sno"];
			int sno = atoi(request->get_query_parameter("sno").c_str());
			std::cout << "Sno ---| " << sno << "|---" << std::endl;
			Transaction t;
			if(t.getTransaction(sno))
			{
				ret = t.toJson();
			}
			else
			{
				ret = no_data;
			}
		}else
		{
			std::vector<Transaction> vec = Transaction::getTrasaction();
			std::cout <<"vector Size:" << vec.size() << std::endl;
 			if(vec.size() > 0)
			{
				ret = getJsonForVector(vec);
			}
			else
			{
				ret = no_data;
			}
		}
		session->close( OK, ret, { { "Content-Length", ::to_string(ret.length()) }, { "Connection", "close" } } );
			} );

}

//Update, single record on Sno
void TransactionService::put_Transaction_controller( const shared_ptr< Session > session )
{
	const auto& request = session->get_request();
	size_t content_length = request->get_header( "Content-Length", 0 );
	session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
			{
		std::string ret;
		const char* c = reinterpret_cast<const char*>(body.data());
		std::string str =std::string(c);
		removeJunkChars(str);
		nlohmann::json js  = nlohmann::json::parse(str);
		std::cout << " Substd::string ---| " << str << "|---" << std::endl;
		int sno = js["sno"];
		std::cout << "Sno ---| " << sno << "|---" << std::endl;
		Transaction t;
		t.getTrasactionFromJson(str);
		if(t.updateTransaction())
		{
			ret = sucess;
		}
		else
		{
			ret = failure;
		}
		session->close( OK, sucess, { { "Content-Length", ::to_string(sucess.length()) }, { "Connection", "close" } } );

			} );
}

//Insert the record
void TransactionService::post_Transaction_controller( const shared_ptr< Session > session )
{
	const auto& request = session->get_request();
	size_t content_length = request->get_header( "Content-Length", 0 );
	session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
			{
		std::string ret;
		const char* c = reinterpret_cast<const char*>(body.data());
		std::string str =std::string(c);
		removeJunkChars(str);
		nlohmann::json js  = nlohmann::json::parse(str);
		std::cout << " Substd::string ---| " << str << "|---" << std::endl;
		int sno = js["sno"];
		std::cout << "Sno ---| " << sno << "|---" << std::endl;
		Transaction t;
		t.getTrasactionFromJson(str);
		if(t.insertTrasaction())
		{
			ret = sucess;
		}
		else
		{
			ret = failure;
		}
		session->close( OK, sucess, { { "Content-Length", ::to_string(sucess.length()) }, { "Connection", "close" } } );
			} );
}

//Insert the record
void TransactionService::delete_Transaction_controller( const shared_ptr< Session > session )
{
	const auto& request = session->get_request();
	size_t content_length = request->get_header( "Content-Length", 0 );
	session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
			{
		std::string ret;
		const char* c = reinterpret_cast<const char*>(body.data());
		std::string str =std::string(c);
		removeJunkChars(str);
		nlohmann::json js  = nlohmann::json::parse(str);
		std::cout << " Substd::string ---| " << str << "|---" << std::endl;
		int sno = js["sno"];
		std::cout << "Sno ---| " << sno << "|---" << std::endl;
		Transaction::deleteTransaction(sno);
		session->close( OK, sucess, { { "Content-Length", ::to_string(sucess.length()) }, { "Connection", "close" } } );
			} );
}

} /* namespace myPay */
