/*
 * lsof -i
 * netstat -lptu
 * netstat -tulpn
 */
#include <iostream>
#include "socket.h"
#include "Method/uaserver.h"
#include <thread>

using namespace EasySip;

UAServer server;

void rxd()
{
	server.start();
}

int main()
{
	std::thread rx(rxd);
	rx.join();

	return 0;
}
