#include <winsock.h>
#include <iostream>
#include <cassert>
#include <string>
#include <thread>
#include "Server.h"

int main()
{
	std::string address;
	std::string name;
	std::string portStr;
	int port;

	std::cout << "Chat: Server mode" << std::endl;
	std::cout << "Enter an IP address to connect to: ";
	std::getline(std::cin, address);
	std::cout << "Enter a port: ";
	std::getline(std::cin, portStr);
	port = std::stoi(portStr);
	std::cin.clear();
	std::cout << "Enter a username: ";
	std::getline(std::cin, name);

	Server server(address, port, name);
	server.Bind();
	server.Listen();
	server.Accept();
	
	std::thread receiveThread = std::thread(&Server::Receive, &server);
	std::thread sendThread = std::thread(&Server::Send, &server);

	receiveThread.join();
	sendThread.join();

	std::cout << "Application finished. Press [Enter] to exit" << std::endl;
	std::cin.get();
	return 0;
}