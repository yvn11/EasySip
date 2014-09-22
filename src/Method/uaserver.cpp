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
		sv_udp_.SelfAddr(Socket::get_ip_addr());//"192.168.0.116");
		//sv_udp_.SelfAddr("192.168.2.8");
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
	int UAServer::on_invite_request(RequestMessage &in_msg)
	{
		in_msg.parse();

		ResponseMessage rep(in_msg);

		rep.add_contact()
		.add_uri("sip:ag@"+sv_udp_.Addr());

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

		sv_udp_.send(rep.create().Msg());

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
