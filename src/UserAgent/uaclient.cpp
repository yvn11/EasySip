/*
 * src/user_agent/uaclient.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "user_agent/uaclient.h"
#include "socket.h"
#include <iostream>

namespace EasySip
{
	int UAClient::invite_request()
	{
		std::string buffer, line;

		while(std::getline(std::cin, line))
			buffer += line;

		InviteMethod invite(buffer);
//		invite.prepare(dest);
//		invite.append_header(key, val);
		SocketIp4UDP sock;
		sock.send(buffer);

		return 0;
	}

	int UAClient::register_request()
	{
		return 0;
	}

	int UAClient::bye_request()
	{
		return 0;
	}

	int UAClient::cancel_request()
	{
		return 0;
	}

	int UAClient::update_request()
	{
		return 0;
	}

	int UAClient::info_request()
	{
		return 0;
	}

	int UAClient::ack_request()
	{
		return 0;
	}

	int UAClient::message_request()
	{
		return 0;
	}

	int UAClient::subscribe_request()
	{
		return 0;
	}

	int UAClient::notify_request()
	{
		return 0;
	}

	int UAClient::refer_request()
	{
		return 0;
	}

	int UAClient::options_request()
	{
		return 0;
	}

	int UAClient::prack_request()
	{
		return 0;
	}

	int UAClient::on_invite_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_register_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_bye_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_cancel_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_ack_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_options_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_subscribe_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_notify_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_info_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_update_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_refer_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_message_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAClient::on_prack_request(RequestMessage &in_msg)
	{
		return 0;
	}

	int UAClient::on_response(Message &in_msg)
	{
		return 0;
	}
} // namespace EasySip
