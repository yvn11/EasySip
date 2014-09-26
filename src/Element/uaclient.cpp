/*
 * src/Element/uaclient.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Element/uaclient.h"

namespace EasySip
{
	UAClient::UAClient()
	{
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(2039);
		udp_.setup_server();
		udp_.Addr(Socket::get_ip_addr());
		udp_.Port(1971);
//		udp_.NeedBind(false);
	}

} // namespace EasySip
