#include "Server.h"

Server::Server(const std::string& address, int port, const std::string& name)
	:
	address(address),
	port(port),
	name(name)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Server::~Server()
{
	WSACleanup();
}

void Server::Bind()
{
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = inet_addr(address.c_str());
	saServer.sin_port = htons(port);

	int result = bind(serverSocket, (sockaddr*)&saServer, sizeof(saServer));
	assert(result != SOCKET_ERROR);
}

void Server::Listen()
{
	int result = listen(serverSocket, SOMAXCONN);
	assert(result != SOCKET_ERROR);
}

void Server::Accept()
{
	std::cout << "Waiting for connecton...";
	SOCKET connectedSocket = accept(serverSocket, nullptr, nullptr);
	assert(connectedSocket != INVALID_SOCKET);
	serverSocket = connectedSocket;
	std::cout << "Connected!" << std::endl;
}

void Server::Send()
{
	while (true)
	{
		std::string message;
		std::getline(std::cin, message);
		message = name + ": " + message;
		send(serverSocket, message.c_str(), (int)message.length() + 1, 0);
	}
}

void Server::Receive()
{
	while (true)
	{
		char buffer[1024];
		int result = recv(serverSocket, buffer, sizeof(buffer), 0);
		if (result == SOCKET_ERROR)
		{
			break;
		}
		std::string message(buffer);
		std::cout << message.c_str() << std::endl;
	}
}
