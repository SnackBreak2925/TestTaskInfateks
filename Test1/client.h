#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include<string>
#ifdef _WIN32

#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<string.h>
#include <fcntl.h>

#endif
class client
{
private:
#ifdef _WIN32
	SOCKADDR_IN serv_addr;
	SOCKET sockfd;
	WSADATA WsaData;
public:
	client(int = 80);
#else
	int sockfd;
	sockaddr_in serv_addr;
public:
	client(int = 80);
#endif
	int port;
	char buffer[10];
public:
	void to_buf(std::string);
	int connection();
	int csend();
	~client();
};

#endif