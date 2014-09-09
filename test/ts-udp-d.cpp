#include <iostream>
#include "socket.h"
#include "user_agent/uaserver.h"

using namespace EasySip;

int main()
{

//	SocketIp4UDP udp;
//	udp.Addr("192.168.2.8");
//	udp.recv();

	UAServer server;
	server.start();
	return 0;
}
