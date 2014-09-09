#include "socket.h"
#include <iostream>

using namespace EasySip;

int main()
{
	SocketIp4UDP udp;

	udp.Addr("192.168.0.116");

	udp.recv();

	return 0;
}
