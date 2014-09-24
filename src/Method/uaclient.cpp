/*
 * src/Method/uaclient.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/uaclient.h"

namespace EasySip
{
	UAClient::UAClient()
	{
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(2039);
//		udp_.setup_server();//NeedBind(false);
		udp_.Addr(Socket::get_ip_addr());
		udp_.Port(1971);
		udp_.NeedBind(false);
	}

//	int UAClient::invite_request()
//	{
//		InviteMessage req;
//
//		req.SipVersion(SIP_VERSION_2_0);
//		req.RequestURI(udp_.Addr());
//
//		req.add_contact()
//		->add_uri("sip:zex@"+udp_.SelfAddr());
//
//		req.add_from()
//		->add_name("zex")
//		.add_uri("sip:zex@"+udp_.SelfAddr())
//		.add_param("tag", "293!hsj@df");
//
//		req.add_to()
//		->add_name("\"Big Boss\"")
//		.add_uri("sip:bigboss@paris.agg.oo");
//
//		req.add_cseq()
//		->add_seq("1")
//		.add_method(req.Method());
//
//		req.add_via()
//		->add_proto(SIP_VERSION_2_0_UDP)
//		.add_sentby(udp_.SelfAddr());
//
//		req.add_call_id()
//		->add_id("sundo@1311bili");
//
//		if (false /*is_sips(req.req_line_.request_uri_) */
//		|| false /*is_sips(req.req_line_.request_uri_) */)
//		{
//			req.add_contact()->add_uri("sips:utoc@ir.cx");
//		}
//
//		req.create();
//
//		udp_.send_buffer(req.Msg());
////		msgq_.push(req.Msg());
////---------------------------------------------------------------
//		if (0 > udp_.recv_buffer(0)) return 0;
//
//		ResponseMessage in_msg(udp_.Message());
//		in_msg.parse();
//
//		if (in_msg.is_2xx_resp())
//		{
//			Dialog dialog(in_msg);
//			dialogs_.create_dialog(dialog);
//	
//			DialogId id = dialogs_.last()->id();
//			std::cout << *dialogs_[id];
//
////			ack_request();
//			udp_.send_buffer(AckMessage(in_msg).create().Msg());
//
////			loop();
//		}
//		else if (in_msg.is_1xx_resp())
//		{
//			std::cout << "peer saids: " << in_msg << '\n';
//		}
//		else
//		{
//			// TODO: invite req failed feedback
//			std::cerr << "Unable to establish session due to "
//				<< in_msg.ResponseCode() << "\n";
//		}
//
//		return 0;
//	}

//	int UAClient::register_request()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//		return 0;
//	}
//
//	int UAClient::bye_request()
//	{
//		ByeMessage req;
//
//		req.SipVersion(SIP_VERSION_2_0);
//
//		if (dialogs_.size())
//		{
//			req.add_to()
//			->add_name("Big Boss\"")
//			.add_uri(dialogs_.last()->remote_uri());
//
//			if (dialogs_.last()->id().remote_tag().size())
//				req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());
//
//			req.add_from()
//			->add_name("zex")
//			.add_uri(dialogs_.last()->local_uri());
//
//			if (dialogs_.last()->id().local_tag().size())
//				req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());
//
//			req.add_call_id()
//			->add_id(dialogs_.last()->id().call_id().id_);
//
//			std::string seq;
//	
//			if (!dialogs_.last()->local_seq().cseq_.empty())
//			{
//				dialogs_.last()->local_seq().inc_seq();
//				seq = dialogs_.last()->local_seq().cseq_;
//			}
//
//			if (seq.empty())
//			{
//				seq = "1"; // TODO: choose a seq, 32bits
//			}
//	
//			req.add_cseq()
//			->add_seq(seq)
//			.add_method(req.Method());
//
//			if (dialogs_.last()->remote_target().size())
//				req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//			if (dialogs_.last()->routes().size())
//			{
//				if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
//				{
////					if (dialogs_.last()->remote_target().size())
//					req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//					req.add_route();
//
//					if (dialogs_.last()->routes().size())
//					{
//						req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
//					}
//				}
//				else
//				{
//					req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());
//
//					req.add_route();
//
//					ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
//					from++;
//
//					req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
//					req.route_.last()->cons_.append(dialogs_.last()->remote_target());
//				}
//			}
//		}
//
//		req.add_via()
//		->add_proto(SIP_VERSION_2_0_UDP)
//		.add_sentby(udp_.SelfAddr());
//
//
//		if (false /*is_sips(req.req_line_.request_uri_) */
//		|| false /*is_sips(req.req_line_.request_uri_) */)
//		{
//			req.add_contact()->add_uri("sips:utoc@ir.cx");
//		}
//
//		req.create();
//		udp_.send_buffer(req.Msg());
////		msgq_.push(req.Msg());
////---------------------------------------------------------------
////		if (0 > udp_.recv_buffer(0)) return 0;
////		ResponseMessage in_msg(udp_.Message());
////		in_msg.parse();
//
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
//		AckMessage req;
//
//		req.SipVersion(SIP_VERSION_2_0);
//
//		if (dialogs_.size())
//		{
//			req.add_to()
//			->add_name("Big Boss\"")
//			.add_uri(dialogs_.last()->remote_uri());
//
//			if (dialogs_.last()->id().remote_tag().size())
//				req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());
//
//			req.add_from()
//			->add_name("zex")
//			.add_uri(dialogs_.last()->local_uri());
//
//			if (dialogs_.last()->id().local_tag().size())
//				req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());
//
//			req.add_call_id()
//			->add_id(dialogs_.last()->id().call_id().id_);
//
//			std::string seq;
//	
//			if (!dialogs_.last()->local_seq().cseq_.empty())
//			{
//				dialogs_.last()->local_seq().inc_seq();
//				seq = dialogs_.last()->local_seq().cseq_;
//			}
//
//			if (seq.empty())
//			{
//				seq = "1"; // TODO: choose a seq, 32bits
//			}
//	
//			req.add_cseq()
//			->add_seq(seq)
//			.add_method(req.Method());
//
//			if (dialogs_.last()->remote_target().size())
//				req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//			if (dialogs_.last()->routes().size())
//			{
//				if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
//				{
////					if (dialogs_.last()->remote_target().size())
//					req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//					req.add_route();
//
//					if (dialogs_.last()->routes().size())
//					{
//						req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
//					}
//				}
//				else
//				{
//					req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());
//
//					req.add_route();
//
//					ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
//					from++;
//
//					req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
//					req.route_.last()->cons_.append(dialogs_.last()->remote_target());
//				}
//			}
//		}
//
//		req.add_via()
//		->add_proto(SIP_VERSION_2_0_UDP)
//		.add_sentby(udp_.SelfAddr());
//
//
//		if (false /*is_sips(req.req_line_.request_uri_) */
//		|| false /*is_sips(req.req_line_.request_uri_) */)
//		{
//			req.add_contact()->add_uri("sips:utoc@ir.cx");
//		}
//
//		req.create();
//		udp_.send_buffer(req.Msg());
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
//		OptionsMessage req;
//
//		req.SipVersion(SIP_VERSION_2_0);
//
//		if (dialogs_.size())
//		{
//			req.add_to()
//			->add_name("Big Boss\"")
//			.add_uri(dialogs_.last()->remote_uri());
//
//			if (dialogs_.last()->id().remote_tag().size())
//				req.to_.last()->add_param("tag", dialogs_.last()->id().remote_tag());
//
//			req.add_from()
//			->add_name("zex")
//			.add_uri(dialogs_.last()->local_uri());
//
//			if (dialogs_.last()->id().local_tag().size())
//				req.from_.last()->add_param("tag", dialogs_.last()->id().local_tag());
//
//			req.add_call_id()
//			->add_id(dialogs_.last()->id().call_id().id_);
//
//			std::string seq;
//	
//			if (!dialogs_.last()->local_seq().cseq_.empty())
//			{
//				dialogs_.last()->local_seq().inc_seq();
//				seq = dialogs_.last()->local_seq().cseq_;
//			}
//
//			if (seq.empty())
//			{
//				seq = "1"; // TODO: choose a seq, 32bits
//			}
//	
//			req.add_cseq()
//			->add_seq(seq)
//			.add_method(req.Method());
//
//			if (dialogs_.last()->remote_target().size())
//				req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//			if (dialogs_.last()->routes().size())
//			{
//				if (dialogs_.last()->routes().last()->cons_.last()->has_param("lr"))
//				{
////					if (dialogs_.last()->remote_target().size())
//					req.RequestURI(dialogs_.last()->remote_target().last()->uri());
//
//					req.add_route();
//
//					if (dialogs_.last()->routes().size())
//					{
//						req.route_.last()->cons_ = dialogs_.last()->routes().last()->cons_;
//					}
//				}
//				else
//				{
//					req.RequestURI(dialogs_.last()->routes().last()->cons_.last()->uri());
//
//					req.add_route();
//
//					ContactList::iterator from = dialogs_.last()->routes().last()->cons_.begin();
//					from++;
//
//					req.route_.last()->cons_.append(from, dialogs_.last()->routes().last()->cons_.end());
//					req.route_.last()->cons_.append(dialogs_.last()->remote_target());
//				}
//			}
//		}
//
//		req.add_via()
//		->add_proto(SIP_VERSION_2_0_UDP)
//		.add_sentby(udp_.SelfAddr());
//
//
//		if (false /*is_sips(req.req_line_.request_uri_) */
//		|| false /*is_sips(req.req_line_.request_uri_) */)
//		{
//			req.add_contact()->add_uri("sips:utoc@ir.cx");
//		}
//
//		req.create();
//		udp_.send_buffer(req.Msg());
////		msgq_.push(req.Msg());
////---------------------------------------------------------------
//		if (0 > udp_.recv_buffer(0)) return 0;
//		ResponseMessage in_msg(udp_.Message());
//		in_msg.parse();
//
//		return 0;
//	}

//	void UAClient::send_msg()
//	{
//		while (run_)
//		{
//			while (msgq_.size())
//			{
//				udp_.send_buffer(msgq_.front());
//				msgq_.pop();
//			}
//		}
//	}
//
//	void UAClient::recv_msg()
//	{
//		while (run_)
//		{
//			udp_.recv_buffer(0);
//			if (udp_.Message().empty()) continue;
//
//			std::string msg(udp_.Message());
//			udp_.clear_msg();
//			on_receive_message(msg);
//		}
//	}
//
//	int UAClient::loop()
//	{
////		std::thread t1(std::bind(&UAClient::send_msg, this));
////		std::thread t2(std::bind(&UAClient::recv_msg, this));
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
