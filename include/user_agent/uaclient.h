#pragma once

#include "user_agent.h"

namespace EasySip
{	
	class UAClient : public UserAgent
	{
	public:
		UAClient()
		{
		}

		~UAClient()
		{
		}

		virtual int on_invite_request(RequestMessage &in_msg);
		virtual int on_register_request(RequestMessage &in_msg);
		virtual int on_bye_request(RequestMessage &in_msg);
		virtual int on_ack_request(RequestMessage &in_msg);
		virtual int on_cancel_request(RequestMessage &in_msg);
		virtual int on_options_request(RequestMessage &in_msg);
		virtual int on_refer_request(RequestMessage &in_msg);
		virtual int on_subscribe_request(RequestMessage &in_msg);
		virtual int on_notify_request(RequestMessage &in_msg);
		virtual int on_message_request(RequestMessage &in_msg);
		virtual int on_info_request(RequestMessage &in_msg);
		virtual int on_prack_request(RequestMessage &in_msg);
		virtual int on_update_request(RequestMessage &in_msg);
		virtual int on_response(Message &in_msg);
	};

} // namespace EasySip
