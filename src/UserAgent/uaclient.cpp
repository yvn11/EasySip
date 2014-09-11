/*
 * src/UserAgent/uaclient.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "UserAgent/uaclient.h"
#include "socket.h"

namespace EasySip
{
		UAClient::UAClient()
		{
			sv_udp_.SelfAddr("192.168.2.8");//0.116");
			sv_udp_.SelfPort(2039);

			cli_udp_.Addr("192.168.2.8");//0.116");
			cli_udp_.Port(1971);
			cli_udp_.NeedBind(false);
		}
//	int UAClient::invite_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		std::string buffer, line;
//
//		while(std::getline(std::cin, line))
//			buffer += line;
//
//		std::cout << "send: " << buffer << '\n';
//		udp_.send(buffer);
//		start();
////		udp_.recv(0);
//		std::cout << "receive: " << udp_.Message() << '\n';
//
//		return 0;
//	}
//
//	int UAClient::register_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::bye_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::cancel_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::update_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::info_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::ack_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::message_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::subscribe_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::notify_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::refer_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::options_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::prack_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::on_invite_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_bye_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_ack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_options_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
} // namespace EasySip
