/*
 * src/Method/uaserver.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/uaserver.h"

namespace EasySip
{
	UAServer::UAServer()
	{
		// TODO: configurable
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(1971);
		udp_.setup_server();
	}

//	int UAServer::invite_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::register_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::bye_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::cancel_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::update_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::info_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::ack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::message_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::subscribe_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::notify_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::refer_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::options_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::prack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::on_invite_request(RequestMessage &in_msg)
//	{
//		ResponseMessage rep(in_msg);
//
//		rep.SipVersion(SIP_VERSION_2_0);
//		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);
//
//		rep.add_contact()
//		->add_uri("sip:ag@"+udp_.Addr());
//
//		if (in_msg.record_route_.size())
//			rep.record_route_ = in_msg.record_route_;
//
//		Dialog dialog(in_msg);
//		dialogs_.create_dialog(dialog);
//
//		std::cout << "----------\n" << *dialogs_.last() << "-----------\n";
//
//		rep.create();
//		udp_.send_buffer(rep.Msg());
//
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_bye_request(RequestMessage &in_msg)
//	{
//		ResponseMessage rep(in_msg);
//	
//		Dialog dialog(in_msg);
//
////		if (in_msg.record_route_.size())
////			rep.record_route_ = in_msg.record_route_;
//
//		dialogs_.cancel_dialog(dialog.id());
//
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//

//	int UAServer::on_ack_request(RequestMessage &in_msg)
//	{
//		Dialog dialog(in_msg);
//
//		if (dialogs_[dialog.id()])
//		{
//			dialogs_[dialog.id()]->is_confirmed(true);
//		}
//
//		return PROCEDURE_OK;
//	}
	
//	int UAServer::on_options_request(RequestMessage &in_msg)
//	{
//		ResponseMessage rep(in_msg);
//
//		rep.SipVersion(SIP_VERSION_2_0);
//		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);
//
//		rep.add_accept()
//		->add_value("text", "plain")
//		.add_value("text", "html")
//		.add_value("application", "sdp")
//		.add_value("multipart", "sdp");
//
//		rep.add_allow();
//
//		for (auto &it : allowed_methods_) 
//			rep.allow_.last()->add_value(it.name());
//
//		udp_.send_buffer(rep.create().Msg());
//
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//	
//	int UAServer::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//
//	int UAServer::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return PROCEDURE_OK;
//	}
//
} // namespace EasySip
