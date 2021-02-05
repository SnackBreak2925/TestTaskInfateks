#include <iostream>
#include <string>
#include "server.h"

using namespace std;

int main()
{
	std::cout << "wait for client" << std::endl;
	while(1)
	{
		server serv;
		serv.recive();
		string rcv = serv.from_buf();
		rcv.shrink_to_fit();
		if((rcv.size() > 2) && !(atoi(rcv.c_str()) % 32))
			std::cout << rcv << endl;
		else
			cout << "incorrect value received" << endl;
	}
	std::cout << "connection ended" << std::endl;
	return 0;
}