/*
 * src/Method/registar.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "Method/registar.h"

namespace EasySip
{
	Registar::Registar()
	{
		// TODO: configurable
		udp_.SelfAddr(Socket::get_ip_addr());
		udp_.SelfPort(5163);
		udp_.setup_server();
	}

//	int Registar::invite_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::register_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::bye_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::cancel_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::update_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::info_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::ack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::message_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::subscribe_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::notify_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::refer_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::options_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::prack_request()
//	{
//		return PROCEDURE_OK;
//	}
//
//	int Registar::on_invite_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		ResponseMessage rep(SIP_RESPONSE_TRYING);
//		udp_.send_buffer(rep.Msg());
//
//		InviteMethod invite(in_msg);
//		invite.parse();
//
//		return PROCEDURE_OK;
//	}
//	
	int Registar::on_register_request(RequestMessage &in_msg)
	{
		in_msg.parse();

		ResponseMessage rep(in_msg);
		rep.SipVersion(SIP_VERSION_2_0);

		// TODO: looking for server, determine whether proxy (Request-URI)

		// TODO: Check HFRequire for extensions

		// TODO: authenticate the UAC, if no auth-mechanism available , check HFFrom address

		// TODO: check if the authenticated user is authorized to modfy registrations for AOR.
		//		check the database where map user names to a list of AOR.
		//		if not authorized, reply with 403 response code and quit
		rep.ResponseCode(SIP_RESPONSE_FORBIDDEN);
		udp_.send_buffer(rep.create().Msg());
		return PROCEDURE_OK;

		// TODO: get AOR from HFTo.
		//		if AOR not valid for domain in Request-URI, reply with 404 response code and quit
		rep.ResponseCode(SIP_RESPONSE_NOT_FOUND);
		udp_.send_buffer(rep.create().Msg());
		return PROCEDURE_OK;

		// check HFContact
		if (in_msg.contact_.size())
		{
			if (1 < in_msg.contact_.size())
			{
				rep.ResponseCode(SIP_RESPONSE_BAD_REQUEST);
				udp_.send_buffer(rep.create().Msg());
				return PROCEDURE_OK;
			}

			for (auto &it : in_msg.contact_.at(0)->cons_)
			{
				if (it->uri() == "*")
				{
					if (in_msg.expires_.size() && in_msg.expires_.at(0)->digit_value_ != "0")
					{
						rep.ResponseCode(SIP_RESPONSE_BAD_REQUEST);
						udp_.send_buffer(rep.create().Msg());
						return PROCEDURE_OK;
					}
				}
			}

		// TODO: check HFCallId, whether agrees with each binding stored
		//		if not, remove the binding
		//		else 
		//			if the in_msg.cseq_ > binding.cseq_
		//			else abort update, request failed
		
			int seconds;

			std::string expire = in_msg.contact_.at(0)->header_params_.get_value_by_name("expires");

			if (expire.empty())
			{
				if (in_msg.expires_.size())
				{
					expire = in_msg.expires_.at(0)->expire();
				}
				else
				{
					// TODO: expire = local expireation
				}
			}

			std::istringstream is(expire);
			is >> seconds;

			if (seconds > 0 && seconds < ONE_HOUR/* TODO && expire < local-min-registrar-timeout */)
			{
				rep.ResponseCode(SIP_RESPONSE_INTERVAL_TOO_BRIEF);
				rep.add_min_expires()->add_value("45");/* TODO: min-expire value*/
				udp_.send_buffer(rep.create().Msg());
				return PROCEDURE_OK;
			}
		}

		rep.ResponseCode(SIP_RESPONSE_SUCCESSFUL);
		// TODO: append HFContact in current bindings with expires param
		//		append HFDate
		udp_.send_buffer(rep.create().Msg());
		return PROCEDURE_OK;
	}
//	
//	int Registar::on_bye_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_cancel_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_ack_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_options_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_subscribe_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_notify_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_info_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_update_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_refer_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_message_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//	
//	int Registar::on_prack_request(RequestMessage &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
//	}
//
//	int Registar::on_response(Message &in_msg)
//	{
//		echo(in_msg);
//		return PROCEDURE_OK;
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
//		return PROCEDURE_OK;
//	}
//
} // namespace EasySip
