/*
 * lsof -i
 * netstat -lptu
 * netstat -tulpn
 */
#include <iostream>
#include "socket.h"
#include "UserAgent/uaserver.h"
#include <thread>

using namespace EasySip;

int main()
{

//	SocketIp4UDP udp;
//	udp.Addr("192.168.2.8");
//	udp.recv();

	UAServer server;
//	std::thread(std::bind(&UAServer::start, server)).join();
	server.start();
	return 0;
}
