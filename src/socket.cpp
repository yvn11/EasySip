/*
 * src/socket.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "socket.h"

// port reuse
//unsigned int yes = 1;
//setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

namespace EasySip
{
	std::string Socket::get_ip_addr()
	{
		std::string ret;
	    struct ifaddrs *ifaddrs = NULL, *ifaddr = NULL;
	    void *tmpAddrPtr = NULL;
		int prot, len;
	
	    getifaddrs(&ifaddrs);
	
	    for (ifaddr = ifaddrs; ifaddr; ifaddr = ifaddr->ifa_next)
		{
	        if (!ifaddr->ifa_addr)
			{
	            continue;
	        }

			if (ifaddr->ifa_addr->sa_family == AF_INET)
			{
	            tmpAddrPtr = &((struct sockaddr_in *)ifaddr->ifa_addr)->sin_addr;
	            len = INET_ADDRSTRLEN;
	            prot = AF_INET;
	        }
			else if (ifaddr->ifa_addr->sa_family == AF_INET6)
			{
	            tmpAddrPtr = &((struct sockaddr_in6 *)ifaddr->ifa_addr)->sin6_addr;
	            len = INET6_ADDRSTRLEN;
				prot = AF_INET6;
				break;
	        }
			else
			{
				continue;
			}


			char addressBuffer[len];
            inet_ntop(prot, tmpAddrPtr, addressBuffer, len);
	        std::cout << ifaddr->ifa_name << "ip: " << addressBuffer << '\n';
			ret = addressBuffer;
	    }

	    if (ifaddrs)
		{
			freeifaddrs(ifaddrs);
		}

	    return ret;
	}

	SocketIp4UDP::SocketIp4UDP()
	: SocketIp4(SOCK_DGRAM), binded_(false), need_bind_(true)
	{
	}

	SocketIp4UDP::SocketIp4UDP(std::string addr, int port)
	: SocketIp4(SOCK_DGRAM), binded_(false), need_bind_(true)
	{
		SelfAddr(addr);
		SelfPort(port);
	}

	SocketIp4UDP::~SocketIp4UDP()
	{
	}

	void SocketIp4UDP::send(const std::string msg)
	{
		sendto(sk_,  msg.c_str(), msg.size(), 0,
			(sockaddr*)&sk_addr_, sizeof(sk_addr_));
	}

	int SocketIp4UDP::recv(int selfloop)
	{
		int ret;

		if (!binded_ && need_bind_)
		{
			if (0 > (ret = bind(sk_, (sockaddr*)&self_sk_addr_, sizeof(self_sk_addr_))))
			{
				// TODO: throw exception
				std::cerr << "bind: " << strerror(errno) << '\n';
				return ret;
			}
			binded_ = true;
		}

		char *buf = new char [max_rx_];
		memset(buf, 0, max_rx_);

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
				std::cerr << "recvfrom: " << strerror(errno) << '\n';
				//TODO: throw error
				break;
			}
			else
			{
				addr_ = inet_ntoa(sk_addr_.sin_addr);
				msg_ = buf;
			}

		} while (selfloop);

		delete buf;
		buf = 0;

		return ret;
	}
} // namespace EasySip
