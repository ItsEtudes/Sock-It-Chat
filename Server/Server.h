#pragma once

#include <winsock.h>
#include <iostream>
#include <cassert>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

class Server
{
public:
	Server(const std::string& address, int port, const std::string& name);
	~Server();
	Server(const Server& server) = delete;
	Server& operator=(const Server& server) = delete;
	void Bind();
	void Listen();
	void Accept();
	void Send();
	void Receive();
private:
	SOCKET serverSocket;
	const std::string address;
	const std::string name;
	int port;
};
