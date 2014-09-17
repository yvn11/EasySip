/*
 * src/Method/uaserver.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/uaserver.h"
#include "socket.h"

namespace EasySip
{
	UAServer::UAServer()
	{
		// TODO: configurable
		//sv_udp_.SelfAddr("192.168.0.116");
		sv_udp_.SelfAddr("192.168.2.8");
		sv_udp_.SelfPort(1971);

		//cli_udp_.Addr("192.168.0.116");
		cli_udp_.Addr("192.168.2.8");
		cli_udp_.Port(9898);
		cli_udp_.NeedBind(false);
	}

//	int UAServer::invite_request()
//	{
//		return 0;
//	}
//
//	int UAServer::register_request()
//	{
//		return 0;
//	}
//
//	int UAServer::bye_request()
//	{
//		return 0;
//	}
//
//	int UAServer::cancel_request()
//	{
//		return 0;
//	}
//
//	int UAServer::update_request()
//	{
//		return 0;
//	}
//
//	int UAServer::info_request()
//	{
//		return 0;
//	}
//
//	int UAServer::ack_request()
//	{
//		return 0;
//	}
//
//	int UAServer::message_request()
//	{
//		return 0;
//	}
//
//	int UAServer::subscribe_request()
//	{
//		return 0;
//	}
//
//	int UAServer::notify_request()
//	{
//		return 0;
//	}
//
//	int UAServer::refer_request()
//	{
//		return 0;
//	}
//
//	int UAServer::options_request()
//	{
//		return 0;
//	}
//
//	int UAServer::prack_request()
//	{
//		return 0;
//	}
//
//	int UAServer::on_invite_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		ResponseMessage rep(SIP_RESPONSE_TRYING);
//		udp_.send(rep.Msg());
//
//		InviteMethod invite(in_msg);
//		invite.parse();
//
//		return 0;
//	}
//	
//	int UAServer::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_bye_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_ack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_options_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAServer::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAServer::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAServer::on_rx_req_exception(RequestMessage &in_msg)
//	{
//		// ---------------------------------------------
//		ResponseMessage resp_msg = in_msg;
//
//		resp_msg.RespStatus(SIP_RESPONSE_METHOD_NOT_ALLOWED);
//
//		resp_msg.allow_.append_field();
//
//		for (MethodMapList::iterator it = allowed_methods_.begin(); it != allowed_methods_.end(); it++)
//			resp_msg.allow_.append_value(it->Name());
//
//		// ---------------------------------------------
//
//		return 0;
//	}
//
} // namespace EasySip
