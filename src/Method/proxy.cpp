/*
 * src/Method/proxy.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/proxy.h"

namespace EasySip
{
	Proxy::Proxy()
	{
		// TODO: configurable
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(7831);
		udp_.setup_server();
	}

//	int Proxy::invite_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::register_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::bye_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::cancel_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::update_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::info_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::ack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::message_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::subscribe_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::notify_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::refer_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::options_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::prack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::on_invite_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		ResponseMessage rep(SIP_RESPONSE_TRYING);
//		udp_.send_buffer(rep.Msg());
//
//		InviteMethod invite(in_msg);
//		invite.parse();
//
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_bye_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_ack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_options_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::on_rx_req_exception(RequestMessage &in_msg)
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
//		return PROCEDURE_OK;
//	}
//
} // namespace EasySip
