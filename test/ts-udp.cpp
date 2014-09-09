#include "socket.h"
#include <iostream>

using namespace EasySip;

int main()
{
	SocketIp4UDP udp;
	udp.Addr("192.168.2.8");
	std::string line;

	while (getline(std::cin, line))
		udp.send(line);

	return 0;
}
