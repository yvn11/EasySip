#include "Method/uaclient.h"
#include <iostream>
#include <thread>

using namespace EasySip;

UAClient client;

void rxd()
{
	client.start();
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
			case 'q':
				PROGRESS_WITH_FEEDBACK("shutdown", client.run(), client.run(false))
				run = 0; break;
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
