#include "Client.h"

Client::Client(const std::string & address, int port, const std::string& name)
	:
	address(address),
	port(port),
	name(name)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Client::~Client()
{
	WSACleanup();
}

void Client::Connect()
{
	sockaddr_in saClient;
	saClient.sin_addr.s_addr = inet_addr(address.c_str());
	saClient.sin_family = AF_INET;
	saClient.sin_port = htons(port);

	connect(clientSocket, (sockaddr*)&saClient, sizeof(saClient));
	std::cout << "Connected!" << std::endl;
}

void Client::Send()
{
	while (true)
	{
		std::string message;
		std::getline(std::cin, message);
		message = name + ": " + message;
		send(clientSocket, message.c_str(), (int)message.length() + 1, 0);
	}
}

void Client::Receive()
{
	while (true)
	{
		char buffer[1024];
		int result = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (result == SOCKET_ERROR)
		{
			break;
		}
		std::string message(buffer);
		std::cout << message.c_str() << std::endl;
	}
}
