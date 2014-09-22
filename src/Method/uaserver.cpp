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
	int UAServer::on_invite_request(RequestMessage &in_msg)
	{
		in_msg.parse();

		ResponseMessage rep(in_msg);

		rep.add_contact()
		->add_uri("sip:ag@"+udp_.Addr());

		rep.SipVersion(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

		dialogs_.create_dialog();

		if (false /*TODO: sent over TLS && in_msg.req_line_->request_uri_ has sip URI */)
		{
			dialogs_.last()->secure_flag(true);
		}

		if (in_msg.record_route_.size())
		{
			rep.record_route_ = in_msg.record_route_;
			dialogs_.last()->routes(in_msg.record_route_);
			std::reverse(dialogs_.last()->routes().begin(), dialogs_.last()->routes().end());
		}
		else
		{
			dialogs_.last()->routes().clear();
		}

		if (in_msg.cseq_.size())
		{
			dialogs_.last()->remote_seq(*in_msg.cseq_.at(0));
		}
//		dialogs_.last()->local_seq_ = UNSET;
		if (in_msg.call_id_.size())
		{
			dialogs_.last()->id().call_id(*in_msg.call_id_.at(0));
		}

		if (in_msg.to_.size())
		{
			dialogs_.last()->id().local_tag(in_msg.to_.at(0)->tag());
			dialogs_.last()->local_uri(in_msg.to_.at(0)->uri());
		}

		if (in_msg.from_.size())
		{
			dialogs_.last()->id().remote_tag(in_msg.from_.at(0)->tag());
			dialogs_.last()->remote_uri(in_msg.from_.at(0)->uri());
		}

		udp_.send_buffer(rep.create().Msg());

		return 0;
	}
//	
//	int UAServer::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
	int UAServer::on_bye_request(RequestMessage &in_msg)
	{
		in_msg.parse();
	
		DialogId val;
	
		val.call_id(*in_msg.call_id_.at(0));
		val.local_tag(in_msg.from_.at(0)->tag());
		val.remote_tag(in_msg.to_.at(0)->tag());

		dialogs_.cancel_dialog(val);

		return 0;
	}
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
	int UAServer::on_options_request(RequestMessage &in_msg)
	{
		in_msg.parse();

		ResponseMessage rep(in_msg);

		rep.SipVersion(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

		rep.add_via()->HeaderParam("received", udp_.Addr());

		rep.add_accept()
		->add_value("text", "plain")
		.add_value("text", "html")
		.add_value("application", "sdp")
		.add_value("multipart", "sdp");

		rep.add_allow();

		for (auto &it : allowed_methods_) 
			rep.allow_.last()->add_value(it.name());

		udp_.send_buffer(rep.create().Msg());

		return 0;
	}
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
} // namespace EasySip
