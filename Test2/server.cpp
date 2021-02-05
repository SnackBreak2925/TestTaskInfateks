#include "server.h"
#include<iostream>

#ifdef _WIN32
server::server(int port)
{
	memset(buffer, 0, sizeof(buffer));
	int err = WSAStartup(0x0101, &WsaData);
	if(err == SOCKET_ERROR)
		throw "WSA start failed" + std::to_string(GetLastError());
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	this->port = port;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // ������� ����� � �����
	listen(listenfd, 10);
	while(connection() != 0)
		Sleep(3000);
}
#else

server::server(int port)
{
	memset(buffer, 0, sizeof(buffer));
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	fcntl(listenfd, F_SETFL, O_NONBLOCK);
	this->port = port;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(listenfd, 10);
	while(connection() != 0)
		sleep(5);
}

#endif

std::string server::from_buf()
{
	std::string a = buffer;
	return a;
}

int server::connection()
{
	unsigned int from = sizeof(serv_addr);
	connfd = accept(listenfd, (struct sockaddr*)&serv_addr, &from);
	fcntl(connfd, F_SETFL, O_NONBLOCK);
	if(connfd == -1)
	{
		std::cout << "client not connected" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "client connected" << std::endl;
		return 0;
	}
}

int server::recive()
{
	int z = recv(connfd, buffer, sizeof(buffer), 0);
	return 0;
}

server::~server()
{
#ifdef _WIN32
	WSACleanup();
	shutdown(listenfd, 0);
	closesocket(listenfd);
#endif
}
