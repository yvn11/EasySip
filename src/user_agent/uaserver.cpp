#include "user_agent/uaserver.h"

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

	int UAServer::on_invite_request(RequestMessage &in_msg)
	{
		InviteMethod invite(in_msg);
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
} // namespace EasySip
