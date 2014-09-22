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

	char c = 'o';
	int run = 1;

	while (run)
	{
		std::cout << "input command: ";
		std::cin >> c;

		switch (c)
		{
			case 'i': client.invite_request(); break;
			case 'r': client.register_request(); break;
			case 'b': client.bye_request(); break;
			case 'c': client.cancel_request(); break;
			case 'u': client.update_request(); break;
			case 'f': client.info_request(); break;
			case 'a': client.ack_request(); break;
			case 'm': client.message_request(); break;
			case 's': client.subscribe_request(); break;
			case 'n': client.notify_request(); break;
			case 'e': client.refer_request(); break;
			case 'o': client.options_request(); break;
			case 'k': client.prack_request(); break;
			case 'q': run = 0; break;
			default:
				std::cerr << "Unexpected command '" << c << "(" << int(c) << ")\n";
		}
	}
//	client.start();
//	std::thread(&UAClient::start, client);//.join();
//	std::thread(std::bind(&UAClient::invite_request, client)).join();

	return 0;
}
