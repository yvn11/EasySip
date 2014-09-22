/*
 * src/Method/uaclient.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/uaclient.h"
#include "socket.h"

namespace EasySip
{
	UAClient::UAClient()
	{
		//sv_udp_.SelfAddr("192.168.0.116");
		//sv_udp_.SelfAddr("192.168.2.8");
		sv_udp_.SelfAddr(Socket::get_ip_addr());//"192.168.0.116");
		sv_udp_.SelfPort(2039);

		//cli_udp_.Addr("192.168.0.116");
		//cli_udp_.Addr("192.168.2.8");
		cli_udp_.Addr(Socket::get_ip_addr());//"192.168.0.116");
		cli_udp_.Port(1971);
		cli_udp_.NeedBind(false);
	}

	int UAClient::invite_request()
	{
		InviteMessage req;

		req.SipVersion(SIP_VERSION_2_0);
		req.RequestURI(cli_udp_.Addr());
		req.add_contact().add_uri("sip:zex@"+sv_udp_.SelfAddr());

		req.add_from()
		.add_name("zex")
		.add_uri("sip:zex@"+sv_udp_.SelfAddr())
		.add_param("tag", "293!hsj@df");

		req.add_to()
		.add_name("\"Big Boss\"")
		.add_uri("sip:bigboss@paris.agg.oo");

		req.add_cseq()
		.add_seq("837133")
		.add_method(req.Method());

		req.add_via()
		.add_proto(SIP_VERSION_2_0_UDP)
		.add_sentby(sv_udp_.SelfAddr());

		req.add_call_id()
		.add_id("sundo@1311bili");

		if (false /*is_sips(req.req_line_.request_uri_) */
		|| false /*is_sips(req.req_line_.request_uri_) */)
		{
			req.add_contact().add_uri("sips:utoc@ir.cx");
		}


		req.create();

		std::cout << "<--------------------\n"
			<< req << "------------------------>\n";
		cli_udp_.send(req.Msg());
		cli_udp_.recv(0);

		ResponseMessage in_msg(cli_udp_.Message());
		in_msg.parse();

		dialogs_.create_dialog();

		if (false /*TODO: sent over TLS && in_msg.req_line_->request_uri_ has sip URI */)
		{
			dialogs_.last()->secure_flag(true);
		}

		if (in_msg.record_route_.size())
		{
			dialogs_.last()->routes(in_msg.record_route_);
			std::reverse(dialogs_.last()->routes().begin(), dialogs_.last()->routes().end());
		}
		else
		{
			dialogs_.last()->routes().clear();
		}

		for (auto &it : in_msg.contact_)
		{
			dialogs_.last()->remote_target().append(it->cons());
		}

//		dialogs_.last()->remote_seq(UNSET);
		dialogs_.last()->local_seq(*in_msg.cseq_.at(0));
		dialogs_.last()->id().call_id(*in_msg.call_id_.at(0));
		dialogs_.last()->id().local_tag(in_msg.from_.at(0)->tag());
		dialogs_.last()->id().remote_tag(in_msg.to_.at(0)->tag());
		dialogs_.last()->remote_uri(in_msg.to_.at(0)->uri());
		dialogs_.last()->local_uri(in_msg.from_.at(0)->uri());

//		sv_udp_.send(req.create().Msg());

		return 0;
	}

//	int UAClient::register_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::bye_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::cancel_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::update_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::info_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::ack_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::message_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::subscribe_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::notify_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::refer_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::options_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::prack_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::on_invite_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_register_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_bye_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_cancel_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_ack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_options_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_subscribe_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_notify_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_info_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_update_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_refer_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_message_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//	
//	int UAClient::on_prack_request(RequestMessage &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::on_response(Message &in_msg)
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
} // namespace EasySip
