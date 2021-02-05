#pragma once
#ifndef SERVER_H
#define SERVER_H
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
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <algorithm>
#include <set>

#endif
class server
{
private:
#ifdef _WIN32
	SOCKADDR_IN serv_addr;
	SOCKET connfd;
	WSADATA WsaData;
public:
	server(int = 80);
#else
	int connfd;
	sockaddr_in serv_addr;
public:
	server(int = 80);
#endif
	int listenfd;
	short port;
	char buffer[10];
public:
	std::string from_buf();
	int connection();
	int recive();
	~server();
};

#endif