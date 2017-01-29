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
#include "../db/getContacts.h"
#include <csignal>
#include <cstring>

using namespace std;
using namespace restbed;

void signal_handler(int signal_)
{
	cout << "Signal received : " << signal_<< endl;
	cout << "Signal Meaning  : " << strerror(signal_) << endl;
}

void get_Hello_handler( const shared_ptr< Session > session )
{
    const auto& request = session->get_request();;

    string body = "Hello";
    //Contacts::getContacts(body, 1);

    try{
    	Contacts::getContacts(body, 1);
    }
    catch(int x)
    {
    	body = "Error Occured";
    }

    cout << "After function" << endl;
    session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

int main( const int, const char** )
{
	signal(SIGINT ,signal_handler);

    auto resource = make_shared< Resource >( );
    resource->set_path( "/Hello" );
    resource->set_method_handler( "GET", get_Hello_handler );


    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish(resource);
    service.start( settings );
    cout << "Waiting for Input" << endl;
    return EXIT_SUCCESS;
}
