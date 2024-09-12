#include "server.h"

boost::asio::io_context 	ServerData::io_context;
std::mutex 					ServerData::client_count_mutex;
int 						ServerData::port				= 12345;
int 						ServerData::client_count 		= 0;

void run_server()
{
	try 
	{
		tcp::acceptor 	acceptor(ServerData::io_context, tcp::endpoint(tcp::v4(), ServerData::port));

		std::cout << "Сервер запущен на порту 12345" << std::endl;

		listen(acceptor);
	}
	catch (std::exception& e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void listen(tcp::acceptor& acceptor)
{
	while (true)
	{
		tcp::socket socket(ServerData::io_context);
		acceptor.accept(socket);
		std::cout << "Клиент подключен" << std::endl;

        std::cout << read_message_from_client(socket) << std::endl;
	}
}

void send_message_to_client(std::string message, tcp::socket& socket)
{
    boost::asio::write(socket, boost::asio::buffer(message));
}

std::string read_message_from_client(tcp::socket& socket)
{
    char buffer[1024];
    size_t len = socket.read_some(boost::asio::buffer(buffer));
    std::string message_from_client(buffer, len);
    
    return message_from_client;
}

void add_client()
{
	std::lock_guard<std::mutex> guard(ServerData::client_count_mutex);
    ServerData::client_count += 1;
    std::cout << "Общее количество клиентов: " << ServerData::client_count << std::endl;
}

void reomve_client()
{
	std::lock_guard<std::mutex> guard(ServerData::client_count_mutex);
    ServerData::client_count -= 1;
    std::cout << "Общее количество клиентов: " << ServerData::client_count << std::endl;
}


int main()
{
	run_server();

	return 0;
}