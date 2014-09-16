/*
 * src/Method/registar.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/registar.h"
#include "socket.h"

namespace EasySip
{
	Registar::Registar()
	{
		// TODO: configurable
		sv_udp_.SelfAddr("192.168.0.116");
		//sv_udp_.SelfAddr("192.168.2.8");
		sv_udp_.SelfPort(3561);

		cli_udp_.Addr("192.168.0.116");
		//cli_udp_.Addr("192.168.2.8");
		cli_udp_.Port(1971);
		cli_udp_.NeedBind(false);
	}

//	int Registar::invite_request()
//	{
//		return 0;
//	}
//
//	int Registar::register_request()
//	{
//		return 0;
//	}
//
//	int Registar::bye_request()
//	{
//		return 0;
//	}
//
//	int Registar::cancel_request()
//	{
//		return 0;
//	}
//
//	int Registar::update_request()
//	{
//		return 0;
//	}
//
//	int Registar::info_request()
//	{
//		return 0;
//	}
//
//	int Registar::ack_request()
//	{
//		return 0;
//	}
//
//	int Registar::message_request()
//	{
//		return 0;
//	}
//
//	int Registar::subscribe_request()
//	{
//		return 0;
//	}
//
//	int Registar::notify_request()
//	{
//		return 0;
//	}
//
//	int Registar::refer_request()
//	{
//		return 0;
//	}
//
//	int Registar::options_request()
//	{
//		return 0;
//	}
//
//	int Registar::prack_request()
//	{
//		return 0;
//	}
//
//	int Registar::on_invite_request(RequestMessage &in_msg)
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
//	int Registar::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_bye_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_ack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_options_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int Registar::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int Registar::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int Registar::on_rx_req_exception(RequestMessage &in_msg)
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
