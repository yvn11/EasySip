/*
 * src/Element/proxy.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Element/proxy.h"

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
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_register_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_bye_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_cancel_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_ack_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_options_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_subscribe_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_notify_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_info_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_update_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_refer_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_message_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Proxy::on_prack_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//
//	int Proxy::on_response(Message &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
} // namespace EasySip
