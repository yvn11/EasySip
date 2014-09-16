#include "Method/uaclient.h"
#include "Method/uaserver.h"
#include <iostream>
#include <thread>

using namespace EasySip;

int main()
{
//	SocketIp4UDP udp;
//	udp.Addr("192.168.0.116");
//	std::string line;
//
//	while (getline(std::cin, line))
//		udp.send(line);

	UAClient client;
	client.invite_request();
//	client.start();
//	std::thread(&UAClient::start, client);//.join();
//	std::thread(std::bind(&UAClient::invite_request, client)).join();

	return 0;
}
