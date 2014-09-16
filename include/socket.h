/*
 * include/socket.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once


#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <error.h>
#include <string.h>
#include "except.h"

namespace EasySip
{
	/*
	 * domain:
	 * AF_UNIX, AF_LOCAL	Local communication			  unix(7)
	 * AF_INET			 IPv4 Internet protocols		  ip(7)
	 * AF_INET6			IPv6 Internet protocols		  ipv6(7)
	 * AF_IPX			  IPX - Novell protocols
	 * AF_NETLINK		  Kernel user interface device	 netlink(7)
	 * AF_X25			  ITU-T X.25 / ISO-8208 protocol	x25(7)
	 * AF_AX25			 Amateur radio AX.25 protocol
	 * AF_ATMPVC			Access to raw ATM PVCs
	 * AF_APPLETALK		Appletalk						ddp(7)
	 * AF_PACKET			Low level packet interface		packet(7)
	 *
	 * type:
	 * SOCK_STREAM
	 * SOCK_DGRAM
	 * SOCK_SEQPACKET
	 * SOCK_RAW
	 * SOCK_RDM
	 * SOCK_PACKET
	 * SOCK_NONBLOCK
	 * SOCK_CLOEXEC
	*/
	class Socket
	{
	protected:

		int sk_;
		int domain_;
		int type_;
		int proto_;

	public:

		Socket()
		{
		}

		Socket(int domain, int type, int proto)
		: domain_(domain), type_(type), proto_(proto)
		{
			sk_ = socket(domain_, type_, proto_);

			// TODO: throw exception
			if (0 > sk_)
				std::cerr << "socket: " << strerror(errno) << '\n';
		}	

		~Socket()
		{
			if (0 < sk_)
				close(sk_);
		}
	};

	class SocketIp4 : public Socket
	{
	protected:

		struct sockaddr_in sk_addr_;
		std::string addr_;

		struct sockaddr_in self_sk_addr_;
		std::string self_addr_;

		std::string msg_;
		int max_rx_;

	public:
		SocketIp4(int type, int proto = 0)
		: Socket(PF_INET, type, proto)
		{
			sk_addr_.sin_family = AF_INET;
			sk_addr_.sin_port = htons(0);
			sk_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

			self_sk_addr_.sin_family = AF_INET;
			self_sk_addr_.sin_port = htons(0);
			self_sk_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

			max_rx_ = 1024;
		}

		int Port()
		{
			return sk_addr_.sin_port;
		}

		void Port(int port)
		{
			sk_addr_.sin_port = htons(port);
		}

		std::string Addr()
		{
			return addr_;
		}

		void Addr(std::string addr)
		{
			addr_ = addr;
			inet_aton(addr_.c_str(), (in_addr*)&sk_addr_.sin_addr.s_addr);
		}

		int SelfPort()
		{
			return self_sk_addr_.sin_port;
		}

		void SelfPort(int port)
		{
			self_sk_addr_.sin_port = htons(port);
		}

		std::string SelfAddr()
		{
			return self_addr_;
		}

		void SelfAddr(std::string addr)
		{
			self_addr_ = addr;
			inet_aton(self_addr_.c_str(), (in_addr*)&self_sk_addr_.sin_addr.s_addr);
		}

		std::string& Message()
		{
			return msg_;
		}

		void Message(std::string msg)
		{
			msg_ = msg;
		}

		int MaxRx()
		{
			return max_rx_;
		}

		void MaxRx(int max)
		{
			max_rx_ = max;
		}

		~SocketIp4()
		{
		}
	};

	class SocketIp4UDP : public SocketIp4
	{
		bool binded_;
		bool need_bind_;
	public:
		SocketIp4UDP();
		SocketIp4UDP(std::string addr, int port);

		~SocketIp4UDP();

		void send(const std::string msg);

		int recv(int selfloop = 1);

		void Bind(bool b)
		{
			binded_ = b;
		}

		void NeedBind(bool b)
		{
			need_bind_ = b;
		}

		bool Bind()
		{
			return binded_;
		}

		bool NeedBind()
		{
			return need_bind_;
		}
	};
} // namespace EasySip
