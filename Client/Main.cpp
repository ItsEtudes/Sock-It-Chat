#include <iostream>
#include <winsock.h>
#include <string>
#include <thread>
#include "Client.h"

int main()
{
	std::string address;
	std::string name;
	std::string portStr;
	int port;

	std::cout << "Chat: Client mode" << std::endl;
	std::cout << "Enter an IP address to connect to: ";
	std::getline(std::cin, address);
	std::cout << "Enter a port: ";
	std::getline(std::cin, portStr);
	port = std::stoi(portStr);
	std::cout << "Enter a username: ";
	std::getline(std::cin, name);

	Client client(address, port, name);
	
	client.Connect();

	std::thread receiveThread = std::thread(&Client::Receive, &client);
	std::thread sendThread = std::thread(&Client::Send, &client);

	receiveThread.join();
	sendThread.join();

	std::cout << "Client application ended. Press [Enter] to exit" << std::endl;
	std::cin.get();
	return 0;
}