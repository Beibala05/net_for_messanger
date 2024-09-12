#include "client.h"

#include <chrono>
#include <thread>


boost::asio::io_context ClientData::io_context;
int 					ClientData::port 		= 12345;

void run_client()
{
	try 
	{
		tcp::socket socket(ClientData::io_context);
    	socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("192.168.0.103"), ClientData::port));
    	std::cout << "Соединение с сервером установлено" << std::endl;

    	send_message_to_server("Hello from client", socket);

    	// std::this_thread::sleep_for(std::chrono::seconds(5));

    	socket.close();

    	std::cout << "Клиент отключен от сервера" << std::endl;
	}
	catch (std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void send_message_to_server(std::string message, tcp::socket& socket)
{
    boost::asio::write(socket, boost::asio::buffer(message));
}

std::string read_message_from_server(tcp::socket& socket)
{
	char buffer[1024];
    size_t len = socket.read_some(boost::asio::buffer(buffer));
    std::string message_from_server(buffer, len);

    return message_from_server;
}

int main()
{
	run_client();

	return 0;
}




// // Проверяем статус подключения
//     if (socket.is_open()) {
//         std::cout << "Сокет открыт." << std::endl;
//         try {
//             tcp::endpoint remote = socket.remote_endpoint();
//             std::cout << "Подключен к: " << remote.address() << ":" << remote.port() << std::endl;
//         } catch (const std::exception& e) {
//             std::cerr << "Ошибка получения удаленного конца: " << e.what() << std::endl;
//         }
//     } else {
//         std::cout << "Сокет закрыт." << std::endl;
//     }

//     // Закрыть сокет, когда он больше не нужен
//     socket.close();