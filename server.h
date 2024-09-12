#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <string>

using boost::asio::ip::tcp;

struct ServerData
{
	static boost::asio::io_context 	io_context;
	static std::mutex 				client_count_mutex;
	static int 						port;
	static int 						client_count;
};

void 								run_server();
void 								listen(tcp::acceptor& acceptor);
void 								add_client();
void 								reomve_client();
void 								send_message_to_client(std::string message, tcp::socket& socket);
std::string 						read_message_from_client(tcp::socket& socket);

#endif // SERVER_H