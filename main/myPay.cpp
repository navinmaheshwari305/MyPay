/*
 * Example illustrating path parameters.
 *
 * Server Usage:
 *    ./distribution/example/path_parameters
 *
 * Client Usage:
 *    curl -w'\n' -v -XGET 'http://localhost:1984/resource/<YOUR NAME HERE>'
 */

#include <string>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <restbed>
#include "../data_layer/Transaction.h"
#include <csignal>
#include <cstring>
#include <vector>
#include "../json/json.hpp"
#include "../utils/MyPayUtils.h"
#include <TransactionService.h>
#include <DbConnection.h>


using namespace std;
using namespace restbed;

//DbConnection* DbConnection::dbCon = nullptr;

void signal_handler(int signal_)
{
	cout << "Signal received : " << signal_<< endl;
	cout << "Signal Meaning  : " << strerror(signal_) << endl;
}

vector<myPay::Transaction> vec;
static string sucess = "{\"Result\":\"Sucess\"}";

void get_Hello_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request();
    string body = myPay::getJsonForVector(vec);
    session->close( OK, body, { { "Content-Length", ::to_string(body.length()) } } );
}
void post_Hello_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request();
    size_t content_length = request->get_header( "Content-Length", 0 );
	session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
	{
		const char* c = reinterpret_cast<const char*>(body.data());
		myPay::Transaction t;
		string str = string(c);
		// std::cout << "Sttr:" << str << std::endl;
		t.getTrasactionFromJson(str);
		vec.push_back(t);

		session->close( OK, sucess, { { "Content-Length", ::to_string(sucess.length()) }, { "Connection", "close" } } );
	} );

}

int main( const int, const char** )
{
	signal(SIGINT ,signal_handler);

	myPay::DbConnection::init_database("navin","root","root");

    auto resource = make_shared< Resource >( );
    resource->set_path( "/Transaction" );
    resource->set_method_handler( "GET", myPay::TransactionService::get_Transaction_controller);
    resource->set_method_handler( "POST", myPay::TransactionService::post_Transaction_controller );
    resource->set_method_handler( "PUT", myPay::TransactionService::put_Transaction_controller );
    resource->set_method_handler( "DELETE", myPay::TransactionService::delete_Transaction_controller );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish(resource);
    service.start( settings );
    cout << "Waiting for Input" << endl;
    return EXIT_SUCCESS;
}
