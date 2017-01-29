/*
 * TransactionService.h
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#ifndef SERVICES_TRANSACTIONSERVICE_H_
#define SERVICES_TRANSACTIONSERVICE_H_

#include <restbed>
#include <memory>
#include <iostream>

using namespace std;
using namespace restbed;

namespace myPay
    {

    class TransactionService
	{
    public:
	TransactionService();
	virtual ~TransactionService();

	//Select All if not path parameter
	//Select one if path parameter
	static void get_Transaction_controller( const shared_ptr< Session > session );

	//Update, single record on Sno
	static void put_Transaction_controller( const shared_ptr< Session > session );

	//Insert the record
	static void post_Transaction_controller( const shared_ptr< Session > session );

	//delete the record
	static void delete_Transaction_controller( const shared_ptr< Session > session );


	};

    } /* namespace myPay */

#endif /* SERVICES_TRANSACTIONSERVICE_H_ */
