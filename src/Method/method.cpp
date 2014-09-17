/*
 * src/Method/method.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/method.h"

namespace EasySip
{
	Method::Method()
	: run_(true)
	{
		HeaderFields::init_allowed_fields();
		init_allowed_methods();
		init_allowed_responses();
	}

	Method::~Method()
	{
	}

	void Method::init_allowed_methods()
	{
		allowed_methods_.insert(METHOD_INVITE);
		allowed_methods_.insert(METHOD_CANCEL);
		allowed_methods_.insert(METHOD_ACK);
		allowed_methods_.insert(METHOD_BYE);
		allowed_methods_.insert(METHOD_REGISTER);
		allowed_methods_.insert(METHOD_OPTIONS);
		allowed_methods_.insert(METHOD_SUBSCRIBE);
		allowed_methods_.insert(METHOD_NOTIFY);
		allowed_methods_.insert(METHOD_MESSAGE);
		allowed_methods_.insert(METHOD_INFO);
		allowed_methods_.insert(METHOD_UPDATE);
		allowed_methods_.insert(METHOD_REFER);
		allowed_methods_.insert(METHOD_PRACK);
	}

	void Method::init_allowed_responses()
	{
		allowed_responses_.insert(SIP_RESPONSE_TRYING);
		allowed_responses_.insert(SIP_RESPONSE_RINGING);
		allowed_responses_.insert(SIP_RESPONSE_FORWARDING);
		allowed_responses_.insert(SIP_RESPONSE_QUEUED);
		allowed_responses_.insert(SIP_RESPONSE_SESSION_PROGRESS);
		allowed_responses_.insert(SIP_RESPONSE_SUCCESSFUL);
		allowed_responses_.insert(SIP_RESPONSE_ACCEPTED);
		allowed_responses_.insert(SIP_RESPONSE_MULTI_CHOICES);
		allowed_responses_.insert(SIP_RESPONSE_MOVE_PERM);
		allowed_responses_.insert(SIP_RESPONSE_MOVE_TEMP);
		allowed_responses_.insert(SIP_RESPONSE_USE_PROXY);
		allowed_responses_.insert(SIP_RESPONSE_ALTER_SERVICE);
		allowed_responses_.insert(SIP_RESPONSE_BAD_REQUEST);
		allowed_responses_.insert(SIP_RESPONSE_UNAUTHORIZED);
		allowed_responses_.insert(SIP_RESPONSE_REQUIRE_PAYMENT);
		allowed_responses_.insert(SIP_RESPONSE_FORBIDDEN);
		allowed_responses_.insert(SIP_RESPONSE_NOT_FOUND);
		allowed_responses_.insert(SIP_RESPONSE_METHOD_NOT_ALLOWED);
		allowed_responses_.insert(SIP_RESPONSE_NOT_ACCEPTABLE);
		allowed_responses_.insert(SIP_RESPONSE_REQUIRE_PROXY_AUTHENTICATION);
		allowed_responses_.insert(SIP_RESPONSE_REQUIRE_REQUEST_TIMEOUT);
		allowed_responses_.insert(SIP_RESPONSE_RESOURCE_NOT_AVAIL);
		allowed_responses_.insert(SIP_RESPONSE_REQUEST_ENTITY_TOO_LARGE);
		allowed_responses_.insert(SIP_RESPONSE_REQUEST_URI_TOO_LONG);
		allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_MEDIA_TYPE);
		allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_URI_SCHEME);
		allowed_responses_.insert(SIP_RESPONSE_BAD_EXTENSION);
		allowed_responses_.insert(SIP_RESPONSE_REQUIRE_EXTENSION);
		allowed_responses_.insert(SIP_RESPONSE_INTERVAL_TOO_BRIEF);
		allowed_responses_.insert(SIP_RESPONSE_UNAVAIL_TEMP);
		allowed_responses_.insert(SIP_RESPONSE_CALL_OR_TRANSACTION_NOT_EXIST);
		allowed_responses_.insert(SIP_RESPONSE_LOOP_DETECTED);
		allowed_responses_.insert(SIP_RESPONSE_TOO_MANY_HOPS);
		allowed_responses_.insert(SIP_RESPONSE_ADDRESS_INCOMPLETE);
		allowed_responses_.insert(SIP_RESPONSE_AMBIGUOUS_URI);
		allowed_responses_.insert(SIP_RESPONSE_BUSY);
		allowed_responses_.insert(SIP_RESPONSE_REQUEST_TERMINATED);
		allowed_responses_.insert(SIP_RESPONSE_NOT_ACCEPTABLE_HERE);
		allowed_responses_.insert(SIP_RESPONSE_REQUEST_PENDING);
		allowed_responses_.insert(SIP_RESPONSE_UNDECIPHERABLE);
		allowed_responses_.insert(SIP_RESPONSE_SERVER_INTERNAL_ERROR);
		allowed_responses_.insert(SIP_RESPONSE_FUNC_NOT_IMPLEMENTED);
		allowed_responses_.insert(SIP_RESPONSE_BAD_GATEWAY);
		allowed_responses_.insert(SIP_RESPONSE_SERVICE_UNAVAIL);
		allowed_responses_.insert(SIP_RESPONSE_SERVICE_TIMEOUT);
		allowed_responses_.insert(SIP_RESPONSE_UNSUPPORTED_VERSION);
		allowed_responses_.insert(SIP_RESPONSE_MESSAGE_TOO_LARGE);
		allowed_responses_.insert(SIP_RESPONSE_GLOBAL_BUSY);
		allowed_responses_.insert(SIP_RESPONSE_CALLEE_DECLINE);
		allowed_responses_.insert(SIP_RESPONSE_GLOBAL_NOT_EXIST);
		allowed_responses_.insert(SIP_RESPONSE_GLOBAL_NOT_ACCEPTABLE);
	}

	int Method::on_receive_message(std::string &msg)
	{
		int ret;

		if (METHOD_INVITE.Code() <= (ret = Message::get_method_from_buffer(allowed_methods_, msg)))
		{
			return on_receive_req(msg, ret);
		}

		if (SIP_RESPONSE_TRYING.Code() <= (ret = Message::get_response_code_from_buffer(allowed_responses_, msg)))
		{
			return on_receive_resp(msg, ret);
		}

		//TODO throw exception ??
		return -1;
	}

	int Method::on_receive_req(std::string &msg, const int code)
	{
		RequestMessage in_msg(msg);

//		return it->Method()(in_msg);
		switch (code)
		{
			case METHOD_ID_INVITE:
			{
				return on_invite_request(in_msg);
			}
			case METHOD_ID_CANCEL:
			{
				return on_cancel_request(in_msg);
			}
			case METHOD_ID_ACK:
			{
				return on_ack_request(in_msg);
			}
			case METHOD_ID_BYE:
			{
				return on_bye_request(in_msg);
			}
			case METHOD_ID_REGISTER:
			{
				return on_register_request(in_msg);
			}
			case METHOD_ID_OPTIONS:
			{
				return on_options_request(in_msg);
			}
			case METHOD_ID_SUBSCRIBE:
			{
				return on_subscribe_request(in_msg);
			}
			case METHOD_ID_NOTIFY:
			{
				return on_notify_request(in_msg);
			}
			case METHOD_ID_MESSAGE:
			{
				return on_message_request(in_msg);
			}
			case METHOD_ID_INFO:
			{
				return on_info_request(in_msg);
			}
			case METHOD_ID_UPDATE:
			{
				return on_update_request(in_msg);
			}
			case METHOD_ID_REFER:
			{
				return on_refer_request(in_msg);
			}
			case METHOD_ID_PRACK:
			{
				return on_prack_request(in_msg);
			}
			default:;
		}

		return 0;
	}

	int Method::on_receive_resp(std::string &msg, const int code)
	{
//		ResponseMessage rep(SIP_RESPONSE_SUCCESSFUL);
////		rep.append_userdata("top of the hill");
//		rep.ResponseVer(SIP_VERSION_2_0);
//		rep.create();
//		sv_udp_.send(rep.Msg());

		ResponseMessage in_msg(msg);
		in_msg.parse();

		return 0;
	}

	void Method::sigint_hdr(int signo)
	{
		std::cout << __PRETTY_FUNCTION__ << "Got signal: " << signo << '\n';
		run_ = false;
	}

	int Method::start()
	{
//		signal(SIGINT, (sighandler_t)&Method::sigint_hdr);
		try
		{
			while (run_)
			{
				sv_udp_.recv(0);
				// TODO: log peer
				std::cout << "peer: <" << sv_udp_.Addr() << ":" << sv_udp_.Port() << ">\n";
				std::string msg(sv_udp_.Message());
				on_receive_message(msg);
			}
		}
		catch (std::exception e)
		{
			std::cout << "exception: " << e.what() << '\n';
			// TODO: log it
		}

		return 0;
	}

	int Method::invite_request()
	{
		std::string buffer, line;

		while(std::getline(std::cin, line))
			buffer += line+'\n';

		std::cout << "send:\n" << buffer << '\n';
		cli_udp_.send(buffer);
		cli_udp_.recv(0);

		
		on_receive_message(cli_udp_.Message());

		return 0;
	}

	int Method::register_request()
	{
		return 0;
	}

	int Method::bye_request()
	{
		return 0;
	}

	int Method::cancel_request()
	{
		return 0;
	}

	int Method::update_request()
	{
		return 0;
	}

	int Method::info_request()
	{
		return 0;
	}

	int Method::ack_request()
	{
		return 0;
	}

	int Method::message_request()
	{
		return 0;
	}

	int Method::subscribe_request()
	{
		return 0;
	}

	int Method::notify_request()
	{
		return 0;
	}

	int Method::refer_request()
	{
		return 0;
	}

	int Method::options_request()
	{
		std::string buffer, line;

		while(std::getline(std::cin, line))
			buffer += line+'\n';

		std::cout << "send:\n" << buffer << '\n';
		cli_udp_.send(buffer);
		cli_udp_.recv(0);
		
		on_receive_message(cli_udp_.Message());

		return 0;
	}

	int Method::prack_request()
	{
		return 0;
	}

	int Method::on_invite_request(RequestMessage &in_msg)
	{
//		InviteMessage msg(in_msg);
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_TRYING);

		// TODO: tag
		rep.to_.at(0)->HeaderParam("tag", "ahelk8.d374");
		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
//		rep.append_userdata("top of the hill");

		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure

		return 0;
	}
	
	int Method::on_register_request(RequestMessage &in_msg)
	{
//		RegisterMessage msg(in_msg);
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_TRYING);

		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
//		rep.append_userdata("top of the hill");

		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure

		return 0;
	}
	
	int Method::on_bye_request(RequestMessage &in_msg)
	{
//		ByeMessage msg(in_msg);
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

		// TODO: tag
		rep.to_.at(0)->HeaderParam("tag", "ahelk8.d374");
		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
//		rep.append_userdata("top of the hill");

		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure
		return 0;
	}
	
	int Method::on_cancel_request(RequestMessage &in_msg)
	{
//		CancelMessage msg(in_msg);
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

		// TODO: tag
		rep.to_.at(0)->HeaderParam("tag", "ahelk8.d374");
		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
//		rep.append_userdata("top of the hill");

		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure
		return 0;
	}
	
	int Method::on_ack_request(RequestMessage &in_msg)
	{
//		AckMessage msg(in_msg);
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

		// TODO: tag
		rep.to_.at(0)->HeaderParam("tag", "ahelk8.d374");
		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
//		rep.append_userdata("top of the hill");

		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure
		return 0;
	}
	
	int Method::on_options_request(RequestMessage &in_msg)
	{
		in_msg.parse();

		ResponseMessage rep(in_msg);

		rep.ResponseVer(SIP_VERSION_2_0);
		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);

//		rep.via_.at(rep.via_.size()-1)->HeaderParam("received", sv_udp_.Addr());
		rep.add_via().HeaderParam("received", sv_udp_.Addr());

		rep.add_accept().add_value("text", "plain")
		.add_value("text", "html")
		.add_value("application", "sdp")
		.add_value("multipart", "sdp");

		rep.add_allow();

		for (auto &it : allowed_methods_)
			(*rep.allow_.end())->add_value(it.Name());


		rep.create();
		sv_udp_.send(rep.Msg());

		// TODO forward procedure
		return 0;
	}
	
	int Method::on_subscribe_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_notify_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_info_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_update_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_refer_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_message_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}
	
	int Method::on_prack_request(RequestMessage &in_msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}

	int Method::on_response(std::string &msg)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return 0;
	}

//	int Method::on_rx_req_exception(RequestMessage &in_msg)
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
} // namespace EasySip
