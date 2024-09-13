#include "client.h"

#include <iostream>
#include <thread>

boost::asio::io_context ClientData::io_context;
int 					ClientData::port 		= 12345;
bool					ClientData::status		= false;


void run_client() 
{
    try 
    {
        tcp::socket socket(ClientData::io_context);
        socket.connect(tcp::endpoint(tcp::v4(), ClientData::port));

        std::cout << "Соединение с сервером установлено" << std::endl;
        ClientData::status = true;

        std::shared_ptr<tcp::socket> socket_ptr = std::make_shared<tcp::socket>(std::move(socket));
        std::thread(read_message_from_server, socket_ptr).detach();

        std::string message_fro_server;

        while (true) 
        {
            std::cout << "Введите сообщение для отправки (или 'exit' для выхода): ";
            std::getline(std::cin, message_fro_server);

            if (message_fro_server == "exit") 
            {
                break; // Выход из цикла, если пользователь ввел "exit"
            }

            send_message_to_server(message_fro_server, socket_ptr);
            std::cout << "Сообщение отправлено: " << message_fro_server << std::endl;
        }

        ClientData::status = false;
        std::cout << "Клиент отключен от сервера" << std::endl;

    } 
    catch (std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}
void send_message_to_server(std::string message, std::shared_ptr<tcp::socket> socket)
{
    boost::asio::write(*socket, boost::asio::buffer(message));
}

void read_message_from_server(std::shared_ptr<tcp::socket> socket)
{
    char buffer[1024];
    boost::system::error_code error;

    while (true)
    {
        size_t len = socket->read_some(boost::asio::buffer(buffer), error);

        if (error) 
        {
            std::cerr << "Ошибка чтения: " << error.message() << std::endl;
            break; // Выход при ошибке
        }

        std::string message_from_server(buffer, len);
        std::cout << "Сообщение от сервера: " << message_from_server << std::endl;
    }
}

int main()
{
	run_client();

	return 0;
}