#include "user_agent/user_agent.h"

namespace EasySip
{
	int UserAgent::on_receive_request(Message &in_msg)
	{
		RequestMessage req_msg = *reinterpret_cast<RequestMessage*>(&in_msg);

		switch(req_msg.method().Code())
		{
			case METHOD_ID_INVITE:
			{
				on_invite_request(req_msg);
				break;
			}
			case METHOD_ID_CANCEL:
			{
				on_cancel_request(req_msg);
				break;
			}
			case METHOD_ID_ACK:
			{
				on_ack_request(req_msg);
				break;
			}
			case METHOD_ID_BYE:
			{
				on_bye_request(req_msg);
				break;
			}
			case METHOD_ID_REGISTER:
			{
				on_register_request(req_msg);
				break;
			}
			case METHOD_ID_OPTIONS:
			{
				on_options_request(req_msg);
				break;
			}
			case METHOD_ID_SUBSCRIBE:
			{
				on_subscribe_request(req_msg);
				break;
			}
			case METHOD_ID_NOTIFY:
			{
				on_notify_request(req_msg);
				break;
			}
			case METHOD_ID_MESSAGE:
			{
				on_message_request(req_msg);
				break;
			}
			case METHOD_ID_INFO:
			{
				on_info_request(req_msg);
				break;
			}
			case METHOD_ID_UPDATE:
			{
				on_update_request(req_msg);
				break;
			}
			default:
			{
				on_rx_req_exception(req_msg);
			}
		};

		return 0;
	}
	
	int UserAgent::on_rx_req_exception(RequestMessage &in_msg)
	{
		return 0;
	}
} // namespace EasySip
