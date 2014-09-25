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

void txd()
{
	char c;
	int run = 1;

	while (run)
	{
		std::cout << "input command: ";
		std::cin >> c;

		switch (c)
		{
			case 'i': server.invite_request(); break;
			case 'r': server.register_request(); break;
			case 'b': server.bye_request(); break;
			case 'c': server.cancel_request(); break;
			case 'u': server.update_request(); break;
			case 'f': server.info_request(); break;
			case 'a': server.ack_request(); break;
			case 'm': server.message_request(); break;
			case 's': server.subscribe_request(); break;
			case 'n': server.notify_request(); break;
			case 'e': server.refer_request(); break;
			case 'o': server.options_request(); break;
			case 'k': server.prack_request(); break;
			case 'q': std::cout << "shutdown ...\n"; while(server.run()) server.run(false); run = 0; break;
			default:
			{
				std::cerr << "Unexpected command '" << c << "(" << int(c) << ")\n";
			}
		}
	}
}

int main()
{
	std::thread tx(txd);
	std::thread rx(rxd);

	tx.join();
	rx.join();

	return 0;
}
