/*
 * include/Method/uaserver.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "method.h"

namespace EasySip
{
	class UAServer : public Method
	{
	public:

		UAServer();

		~UAServer()
		{
		}

//		virtual int invite_request();
//		virtual int register_request();
//		virtual int bye_request();
//		virtual int cancel_request();
//		virtual int update_request();
//		virtual int info_request();
//		virtual int ack_request();
//		virtual int message_request();
//		virtual int subscribe_request();
//		virtual int notify_request();
//		virtual int refer_request();
//		virtual int options_request();
//		virtual int prack_request();
//
		virtual int on_invite_request(RequestMessage &in_msg);
//		virtual int on_register_request(RequestMessage &in_msg);
		virtual int on_bye_request(RequestMessage &in_msg);
//		virtual int on_ack_request(RequestMessage &in_msg);
//		virtual int on_cancel_request(RequestMessage &in_msg);
		virtual int on_options_request(RequestMessage &in_msg);
//		virtual int on_refer_request(RequestMessage &in_msg);
//		virtual int on_subscribe_request(RequestMessage &in_msg);
//		virtual int on_notify_request(RequestMessage &in_msg);
//		virtual int on_message_request(RequestMessage &in_msg);
//		virtual int on_info_request(RequestMessage &in_msg);
//		virtual int on_prack_request(RequestMessage &in_msg);
//		virtual int on_update_request(RequestMessage &in_msg);
//		virtual int on_response(Message &in_msg);
//		virtual int on_rx_req_exception(RequestMessage &in_msg);
	};

} // namespace EasySip
