#pragma once

#include <iostream>
#include <winsock.h>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client(const std::string& address, int port, const std::string& name);
	~Client();
	Client(const Client& client) = delete;
	Client& operator=(const Client& client) = delete;
	void Connect();
	void Send();
	void Receive();
private:
	SOCKET clientSocket;
	const std::string address;
	const std::string name;
	int port;
};
