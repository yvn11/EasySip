/*
 * include/user_agent/user_agent.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "method.h"

namespace EasySip
{
	class UserAgent// : public Methods
	{
	public:
		UserAgent()
		{
		}

		~UserAgent()
		{
		}

		virtual int on_receive_request(Message &in_msg);
		virtual int on_rx_req_exception(RequestMessage &in_msg);

		virtual int invite_request() = 0;
		virtual int register_request() = 0;
		virtual int bye_request() = 0;
		virtual int cancel_request() = 0;
		virtual int update_request() = 0;
		virtual int info_request() = 0;
		virtual int ack_request() = 0;
		virtual int message_request() = 0;
		virtual int subscribe_request() = 0;
		virtual int notify_request() = 0;
		virtual int refer_request() = 0;
		virtual int options_request() = 0;
		virtual int prack_request() = 0;

		virtual int on_invite_request(RequestMessage &in_msg) = 0;
		virtual int on_register_request(RequestMessage &in_msg) = 0;
		virtual int on_bye_request(RequestMessage &in_msg) = 0;
		virtual int on_ack_request(RequestMessage &in_msg) = 0;
		virtual int on_cancel_request(RequestMessage &in_msg) = 0;
		virtual int on_options_request(RequestMessage &in_msg) = 0;
		virtual int on_refer_request(RequestMessage &in_msg) = 0;
		virtual int on_subscribe_request(RequestMessage &in_msg) = 0;
		virtual int on_notify_request(RequestMessage &in_msg) = 0;
		virtual int on_message_request(RequestMessage &in_msg) = 0;
		virtual int on_info_request(RequestMessage &in_msg) = 0;
		virtual int on_prack_request(RequestMessage &in_msg) = 0;
		virtual int on_update_request(RequestMessage &in_msg) = 0;
		virtual int on_response(Message &in_msg) = 0;
	};

} // namespace EasySip
