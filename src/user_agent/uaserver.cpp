/*
 * src/user_agent/uaserver.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "user_agent/uaserver.h"
#include "socket.h"

namespace EasySip
{
	void UAServer::init_allowed_methods()
	{
		allowed_methods_.insert(METHOD_INVITE);
		allowed_methods_.insert(METHOD_CANCEL);
		allowed_methods_.insert(METHOD_ACK);
		allowed_methods_.insert(METHOD_BYE);
		allowed_methods_.insert(METHOD_REGISTER);
		allowed_methods_.insert(METHOD_OPTIONS);
		allowed_methods_.insert(METHOD_SUBSCRIBE);
		allowed_methods_.insert(METHOD_NOTIFY);
		allowed_methods_.insert(METHOD_MESSAGE);
		allowed_methods_.insert(METHOD_INFO);
		allowed_methods_.insert(METHOD_UPDATE);
		allowed_methods_.insert(METHOD_REFER);
		allowed_methods_.insert(METHOD_PRACK);
	}

	int UAServer::invite_request()
	{
		return 0;
	}

	int UAServer::register_request()
	{
		return 0;
	}

	int UAServer::bye_request()
	{
		return 0;
	}

	int UAServer::cancel_request()
	{
		return 0;
	}

	int UAServer::update_request()
	{
		return 0;
	}

	int UAServer::info_request()
	{
		return 0;
	}

	int UAServer::ack_request()
	{
		return 0;
	}

	int UAServer::message_request()
	{
		return 0;
	}

	int UAServer::subscribe_request()
	{
		return 0;
	}

	int UAServer::notify_request()
	{
		return 0;
	}

	int UAServer::refer_request()
	{
		return 0;
	}

	int UAServer::options_request()
	{
		return 0;
	}

	int UAServer::prack_request()
	{
		return 0;
	}

	int UAServer::on_invite_request(RequestMessage &in_msg)
	{
		InviteMethod invite;//(in_msg);
		invite.parse_header();

		return 0;
	}
	
	int UAServer::on_register_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_bye_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_cancel_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_ack_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_options_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_subscribe_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_notify_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_info_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_update_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_refer_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_message_request(RequestMessage &in_msg)
	{
		return 0;
	}
	
	int UAServer::on_prack_request(RequestMessage &in_msg)
	{
		return 0;
	}

	int UAServer::on_response(Message &in_msg)
	{
		return 0;
	}

	int UAServer::on_rx_req_exception(RequestMessage &in_msg)
	{
		// ---------------------------------------------
		ResponseMessage resp_msg = in_msg;

		resp_msg.RespStatus(SIP_RESPONSE_METHOD_NOT_ALLOWED);

		resp_msg.allow_.append_field();

		for (MethodMapList::iterator it = allowed_methods_.begin(); it != allowed_methods_.end(); it++)
			resp_msg.allow_.append_value(it->Name());

		// ---------------------------------------------

		return 0;
	}

	int UAServer::start()
	{
		SocketIp4UDP udp;

		udp.Addr("192.168.0.116");

		while (1)
		{
			udp.recv(0);
		}

		return 0;
	}
} // namespace EasySip
