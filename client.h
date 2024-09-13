#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct ClientData
{
	static boost::asio::io_context	io_context;
	static int 						port;
	static bool						status;
};

void 								run_client();
void 								send_message_to_server(std::string message, std::shared_ptr<tcp::socket> socket);
void 								read_message_from_server(std::shared_ptr<tcp::socket> socket);

#endif // CLIENT_H