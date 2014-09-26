#include "Element/proxy.h"
#include <iostream>
#include <thread>

using namespace EasySip;

Proxy proxy;

void rxd()
{
	proxy.start();
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
			case 'i': proxy.invite_request(); break;
			case 'r': proxy.register_request(); break;
			case 'b': proxy.bye_request(); break;
			case 'c': proxy.cancel_request(); break;
			case 'u': proxy.update_request(); break;
			case 'f': proxy.info_request(); break;
			case 'a': proxy.ack_request(); break;
			case 'm': proxy.message_request(); break;
			case 's': proxy.subscribe_request(); break;
			case 'n': proxy.notify_request(); break;
			case 'e': proxy.refer_request(); break;
			case 'o': proxy.options_request(); break;
			case 'k': proxy.prack_request(); break;
			case 'q':
				PROGRESS_WITH_FEEDBACK("shutdown", proxy.run(), proxy.run(false))
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
