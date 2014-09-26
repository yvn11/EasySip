/*
 * src/Method/uaserver.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/uaserver.h"

namespace EasySip
{
	UAServer::UAServer()
	{
		// TODO: configurable
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(1971);
		udp_.setup_server();
	}

} // namespace EasySip
