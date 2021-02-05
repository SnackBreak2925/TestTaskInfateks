#include "client.h"
#include<iostream>

#ifdef _WIN32

client::client(int port)
{
	int err = WSAStartup(0x0101, &WsaData);
	if(err == SOCKET_ERROR)
		throw "WSA start failed" + std::to_string(GetLastError());
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw "create socket error";
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
		throw "inet_pton() error";
	while(connection() != 0)
		Sleep(2000);
}

#else

client::client(int port)
{
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw "create socket error";
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
		throw "inet_pton() error";
	while(connection() != 0)
		sleep(5);
}

#endif

void client::to_buf(std::string in)
{
	in.copy(buffer, in.size() + 1);
	buffer[in.size()] = '\0';
}

int client::connection()
{
	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "connection to server failed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "connected to server" << std::endl;
		return 0;
	}
}

int client::csend()
{
#ifdef _WIN32
	Sleep(1000);
#else
	sleep(2);
#endif
	send(sockfd, buffer, sizeof(buffer), 0);
	return 0;
}

client::~client()
{
#ifdef _WIN32
	WSACleanup();
	shutdown(sockfd, 0);
	closesocket(sockfd);
#endif
}