#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct ClientData
{
	static boost::asio::io_context	io_context;
	static int 						port;
};

void 								run_client();
void 								send_message_to_server(std::string message, tcp::socket& socket);
std::string 						read_message_from_server(tcp::socket& socket);

#endif // CLIENT_H