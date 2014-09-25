/*
 * src/socket.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "socket.h"
#include "buffer.h"

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


			Buffer addr_buf(len);
            inet_ntop(prot, tmpAddrPtr, addr_buf.data(), addr_buf.len());
	        std::cout << "IF: " << ifaddr->ifa_name << " IP: " << addr_buf.data() << '\n';
			ret = addr_buf.data();
	    }

	    if (ifaddrs)
		{
			freeifaddrs(ifaddrs);
		}

	    return ret;
	}

	int Socket::set_timeout(int sec)
	{
		int ret;

		struct timeval tv;
		tv.tv_sec = sec;
		tv.tv_usec = 0;

		if (0 > (ret = setsockopt(sk_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))))
				std::cerr << "socket: " << strerror(errno) << '\n';

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

	void SocketIp4UDP::send_buffer(const std::string msg)
	{
		sendto(sk_,  msg.c_str(), msg.size(), 0,
			(sockaddr*)&sk_addr_, sizeof(sk_addr_));
	}

	int SocketIp4UDP::setup_server()
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

		return ret;
	}

	int SocketIp4UDP::recv_buffer(int selfloop)
	{
		int ret;
		Buffer buf(max_rx_);
		socklen_t len = sizeof(sk_addr_);

//		fd_set r_fds;
//		struct timeval tv;

		do
		{
//			FD_ZERO(&r_fds);
//			FD_SET(sk_, &r_fds);
//			tv.tv_sec = 3;
//			tv.tv_usec = 10;
//
//			select(sk_+1, &r_fds, 0, 0, &tv);
//
//			if (FD_ISSET(sk_, &r_fds))
			{
				if ((ret = recvfrom(sk_, buf.data(), buf.len(), 0,
					(sockaddr*)&sk_addr_, &len)) == 0)
				{
				//	break;
				}
				else if (ret < 0)
				{
					if (errno == EAGAIN) break;

					std::cerr << "recvfrom: " << strerror(errno) << '\n';
					break;
				}
				else
				{
					addr_ = inet_ntoa(sk_addr_.sin_addr);
					msg_ = buf.data();
				}
			}
		} while (selfloop);

		return ret;
	}
} // namespace EasySip
