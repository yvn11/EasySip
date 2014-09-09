/*
 * src/socket.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "socket.h"

namespace EasySip
{
	SocketIp4UDP::SocketIp4UDP()
	: SocketIp4(SOCK_DGRAM)
	{
	}

	SocketIp4UDP::~SocketIp4UDP()
	{
	}

	void SocketIp4UDP::send(std::string msg)
	{
		sendto(sk_,  msg.c_str(), msg.size(), 0,
			(sockaddr*)&sk_addr_, sizeof(sk_addr_));
	}

	int SocketIp4UDP::recv(int selfloop)
	{
		bind(sk_, (sockaddr*)&sk_addr_, sizeof(sk_addr_));

		char *buf = new char [max_rx_];
		int ret;
		socklen_t len = sizeof(sk_addr_);

		do
		{
			if ((ret = recvfrom(sk_, buf, max_rx_, 0,
				(sockaddr*)&sk_addr_, &len)) == 0)
			{
				break;
			}
			else if (ret < 0)
			{
				std::cout << "error: " << strerror(errno) << '\n';
				//TODO: throw error
			}
			else
			{
				msg_ += buf;
			}

			std::cout << "msg: " << msg_ << '\n';
		} while (selfloop);

		delete buf;

		return ret;
	}
} // namespace EasySip
