/*
 * src/message.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "message.h"

namespace EasySip
{
	std::ostream& operator<< (std::ostream& o, Message& msg)
	{
		out_if_not_null(o, msg.call_id_);
		out_if_not_null(o, msg.cseq_);
		out_if_not_null(o, msg.from_);
		out_if_not_null(o, msg.to_);

		for (std::vector<std::shared_ptr<HFVia> >::iterator it = msg.via_.begin();
			it != msg.via_.end(); it++)
			o << **it;
			
		out_if_not_null(o, msg.alert_info_);
		out_if_not_null(o, msg.allow_events_);
		out_if_not_null(o, msg.date_);
		out_if_not_null(o, msg.contact_);
		out_if_not_null(o, msg.organization_);
		out_if_not_null(o, msg.record_route_);
		out_if_not_null(o, msg.retry_after_);
		out_if_not_null(o, msg.subject_);
		out_if_not_null(o, msg.supported_);
		out_if_not_null(o, msg.timestamp_);
		out_if_not_null(o, msg.user_agent_);
		out_if_not_null(o, msg.answer_mode_);
		out_if_not_null(o, msg.priv_answer_mode_);
		out_if_not_null(o, msg.accept_);
		out_if_not_null(o, msg.accept_contact_);
		out_if_not_null(o, msg.accept_encoding_);
		out_if_not_null(o, msg.accept_language_);
		out_if_not_null(o, msg.authorization_);
		out_if_not_null(o, msg.call_info_);
		out_if_not_null(o, msg.event_);
		out_if_not_null(o, msg.in_replay_to_);
		out_if_not_null(o, msg.join_);
		out_if_not_null(o, msg.priority_);
		out_if_not_null(o, msg.privacy_);
		out_if_not_null(o, msg.proxy_authorization_);
		out_if_not_null(o, msg.proxy_require_);
		out_if_not_null(o, msg.p_osp_auth_token_);
		out_if_not_null(o, msg.p_asserted_identity_);
		out_if_not_null(o, msg.p_preferred_identity_);
		out_if_not_null(o, msg.max_forwards_);
		out_if_not_null(o, msg.reason_);
		out_if_not_null(o, msg.refer_to_);
		out_if_not_null(o, msg.referred_by_);
		out_if_not_null(o, msg.reply_to_);
		out_if_not_null(o, msg.replaces_);
		out_if_not_null(o, msg.reject_contact_);
		out_if_not_null(o, msg.request_disposition_);
		out_if_not_null(o, msg.require_);
		out_if_not_null(o, msg.route_);
		out_if_not_null(o, msg.rack_);
		out_if_not_null(o, msg.session_expires_);
		out_if_not_null(o, msg.subscription_state_);
		out_if_not_null(o, msg.authentication_info_);
		out_if_not_null(o, msg.error_info_);
		out_if_not_null(o, msg.min_expires_);
		out_if_not_null(o, msg.min_se_);
		out_if_not_null(o, msg.proxy_authenticate_);
		out_if_not_null(o, msg.server_);
		out_if_not_null(o, msg.unsupported_);
		out_if_not_null(o, msg.warning_);
		out_if_not_null(o, msg.www_authenticate_);
		out_if_not_null(o, msg.rseq_);
		out_if_not_null(o, msg.allow_);
		out_if_not_null(o, msg.content_encoding_);
		out_if_not_null(o, msg.content_length_);
		out_if_not_null(o, msg.content_language_);
		out_if_not_null(o, msg.content_type_);
		out_if_not_null(o, msg.expires_);
		out_if_not_null(o, msg.mime_version_);

		o << msg.user_data_;

		return o;
	}

	Message& Message::create()
	{
		if (!is_valid())
		{
			// TODO: thown exception and log this
			std::cerr << __PRETTY_FUNCTION__ << ": message invalid!\n";
			return *this;
		}

		std::ostringstream o;
		o << user_data_.size();

		content_length_ = std::make_shared<HFContentLength>();
		content_length_->digit_value_ = o.str();

		return *this;
	}

	bool Message::is_valid()
	{
		return_false_if_true(call_id_ == 0) 
		return_false_if_true(cseq_ == 0) 
		return_false_if_true(from_ == 0) 
		return_false_if_true(to_ == 0) 
		return_false_if_true(via_.empty()) 
//		return_false_if_true(max_forwards_ == 0 && resp_status_ == 0) 

		return true;
	}

	int Message::get_method_from_buffer(
		MethodMapList &allowed_methods, std::string msg, std::string sym)
	{
		MethodMapList::iterator it;
		std::string ret = msg.substr(0, msg.find_first_of(sym));

		for (it = allowed_methods.begin(); it != allowed_methods.end(); it++)
		{
			if (ret == it->Name())
				return it->Code();
		}

		return -1;
	}

	int Message::get_response_code_from_buffer(
		RespCodeList &allowed_responses, std::string msg, std::string sym)
	{
		RespCodeList::iterator it;
		size_t pos = msg.find_first_of(sym);

		if (pos == std::string::npos)
			return -1;

		pos++;
		int next = msg.find_first_of(sym, pos);
		std::string ret = msg.substr(pos, next-pos);

		for (it = allowed_responses.begin(); it != allowed_responses.end(); it++)
		{
			if (ret == it->CodeStr())
				return it->Code();
		}

		return -1;
	}

	std::vector<std::string> Message::split_by(std::string msg, std::string sym)
	{
		size_t pos, next;
		std::vector<std::string> ret;

		for (next = pos = 0; ; pos = next+1)
		{
			next = msg.find_first_of(sym, pos);
			if (next == std::string::npos)
				break;

			ret.push_back(msg.substr(pos, next-pos));
		}

		return ret;
	}

	void Message::parse_dispatch(std::string field, size_t &pos)
	{
		if (HFVia().Field() == field || HFVia().Compact() == field)
		{
			via_.push_back(std::make_shared<HFVia>());
			via_.at(via_.size()-1)->parse(msg_, pos);
			return;
		}

		parse_dispatch_if_match<HFCallId>(call_id_, field, msg_, pos);
		parse_dispatch_if_match<HFCSeq>(cseq_, field, msg_, pos);
		parse_dispatch_if_match<HFFrom>(from_, field, msg_, pos);
		parse_dispatch_if_match<HFTo>(to_, field, msg_, pos);

		parse_dispatch_if_match<HFAlertInfo>(alert_info_, field, msg_, pos);
		parse_dispatch_if_match<HFAllowEvents>(allow_events_, field, msg_, pos);
		parse_dispatch_if_match<HFDate>(date_, field, msg_, pos);
		parse_dispatch_if_match<HFContact>(contact_, field, msg_, pos);
		parse_dispatch_if_match<HFOrganization>(organization_, field, msg_, pos);
		parse_dispatch_if_match<HFRecordRoute>(record_route_, field, msg_, pos);
		parse_dispatch_if_match<HFRetryAfter>(retry_after_, field, msg_, pos); // in second
		parse_dispatch_if_match<HFSubject>(subject_, field, msg_, pos);
		parse_dispatch_if_match<HFSupported>(supported_, field, msg_, pos);
		parse_dispatch_if_match<HFTimestamp>(timestamp_, field, msg_, pos);
		parse_dispatch_if_match<HFUserAgent>(user_agent_, field, msg_, pos);
		parse_dispatch_if_match<HFAnswerMode>(answer_mode_, field, msg_, pos);
		parse_dispatch_if_match<HFPrivAnswerMode>(priv_answer_mode_, field, msg_, pos);
		parse_dispatch_if_match<HFAccept>(accept_, field, msg_, pos); // type/sub-type
		parse_dispatch_if_match<HFAcceptContact>(accept_contact_, field, msg_, pos);
		parse_dispatch_if_match<HFAcceptEncoding>(accept_encoding_, field, msg_, pos);
		parse_dispatch_if_match<HFAcceptLanguage>(accept_language_, field, msg_, pos);
		parse_dispatch_if_match<HFAuthorization>(authorization_, field, msg_, pos);
		parse_dispatch_if_match<HFCallInfo>(call_info_, field, msg_, pos);
		parse_dispatch_if_match<HFEvent>(event_, field, msg_, pos);
		parse_dispatch_if_match<HFInReplyTo>(in_replay_to_, field, msg_, pos);
		parse_dispatch_if_match<HFJoin>(join_, field, msg_, pos);
		parse_dispatch_if_match<HFPriority>(priority_, field, msg_, pos);
		parse_dispatch_if_match<HFPrivacy>(privacy_, field, msg_, pos);
		parse_dispatch_if_match<HFProxyAuthorization>(proxy_authorization_, field, msg_, pos);
		parse_dispatch_if_match<HFProxyRequire>(proxy_require_, field, msg_, pos);
		parse_dispatch_if_match<HFPOSPAuthToken>(p_osp_auth_token_, field, msg_, pos);
		parse_dispatch_if_match<HFPAssertedIdentity>(p_asserted_identity_, field, msg_, pos);
		parse_dispatch_if_match<HFPPreferredIdentity>(p_preferred_identity_, field, msg_, pos);
		parse_dispatch_if_match<HFMaxForwards>(max_forwards_, field, msg_, pos);
		parse_dispatch_if_match<HFReason>(reason_, field, msg_, pos);
		parse_dispatch_if_match<HFReferTo>(refer_to_, field, msg_, pos);
		parse_dispatch_if_match<HFReferredBy>(referred_by_, field, msg_, pos);
		parse_dispatch_if_match<HFReplyTo>(reply_to_, field, msg_, pos);
		parse_dispatch_if_match<HFReplaces>(replaces_, field, msg_, pos);
		parse_dispatch_if_match<HFRejectContact>(reject_contact_, field, msg_, pos);
		parse_dispatch_if_match<HFRequestDisposition>(request_disposition_, field, msg_, pos);
		parse_dispatch_if_match<HFRequire>(require_, field, msg_, pos);
		parse_dispatch_if_match<HFRoute>(route_, field, msg_, pos);
		parse_dispatch_if_match<HFRack>(rack_, field, msg_, pos);
		parse_dispatch_if_match<HFSessionExpires>(session_expires_, field, msg_, pos); // in second
		parse_dispatch_if_match<HFSubscriptionState>(subscription_state_, field, msg_, pos);
		parse_dispatch_if_match<HFAuthenticationInfo>(authentication_info_, field, msg_, pos);
		parse_dispatch_if_match<HFErrorInfo>(error_info_, field, msg_, pos);
		parse_dispatch_if_match<HFMinExpires>(min_expires_, field, msg_, pos);
		parse_dispatch_if_match<HFMinSE>(min_se_, field, msg_, pos);
		parse_dispatch_if_match<HFProxyAuthenticate>(proxy_authenticate_, field, msg_, pos);
		parse_dispatch_if_match<HFServer>(server_, field, msg_, pos);
		parse_dispatch_if_match<HFUnsupported>(unsupported_, field, msg_, pos);
		parse_dispatch_if_match<HFWarning>(warning_, field, msg_, pos);
		parse_dispatch_if_match<HFWWWAuthenticate>(www_authenticate_, field, msg_, pos);
		parse_dispatch_if_match<HFRSeq>(rseq_, field, msg_, pos);
		parse_dispatch_if_match<HFAllow>(allow_, field, msg_, pos);
		parse_dispatch_if_match<HFContentEncoding>(content_encoding_, field, msg_, pos);
		parse_dispatch_if_match<HFContentLength>(content_length_, field, msg_, pos);
		parse_dispatch_if_match<HFContentLanguage>(content_language_, field, msg_, pos);
		parse_dispatch_if_match<HFContentType>(content_type_, field, msg_, pos);
		parse_dispatch_if_match<HFExpires>(expires_, field, msg_, pos); // in second
		parse_dispatch_if_match<HFMIMEVersion>(mime_version_, field, msg_, pos);
	}

	/* parse buffered header into formated header fields
	 */
	void Message::parse(size_t &pos)
	{
		if (msg_.empty()) return;

		bool run = true;
		std::string buffer;

		while (run)
		{
			if (pos+1 >= msg_.size()) break;
//			if (content_length_) break;

			switch(msg_.at(pos))
			{
				CASE_ALPHA
				case '-':
				{
					buffer += msg_.at(pos++);
					break;
				}
				case '\r':
				case '\n':
				{
					pos++;
					buffer.clear();
					break;
				}
				case ':':
				{
					pos++;
					std::cout << "field: " << buffer << '\n';

					parse_dispatch(buffer, pos);
					buffer.clear();

					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg_.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		if (content_length_)
		{
			size_t i = 1, len = 0;
			std::istringstream in(content_length_->digit_value_);
			in >> len;
	
			while (pos < msg_.size() && i < len)
			{
				buffer += msg_.at(pos++);
			}

			user_data_ = buffer;
		}
	}

	RequestMessage& RequestMessage::create()
	{
		//Base::create();
		std::ostringstream o;

		o << req_line_ << '\n';
		o << *this;

		msg_ = o.str();

		return *this;
	}

	void RequestMessage::parse(size_t &pos)
	{
		if (msg_.empty()) return;

		req_line_->parse(msg_, pos);

		Base::parse(pos);

		if (!is_valid())
		{
			std::cerr << __PRETTY_FUNCTION__ << ": message invalid!\n";
		}

		std::cout << "-request------------------------\n";
		std::cout << *req_line_ << '\n';
		std::cout << *this;
		std::cout << "--------------------------------\n";
	}

	bool InviteMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return_false_if_true(contact_ == 0)

		return true;
	}
	// RegisterMessage
	bool RegisterMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())

		if (record_route_) delete &record_route_;

		return true;
	}
	// AckMessage
	bool AckMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// ByeMessage
	bool ByeMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// CancelMessage
	bool CancelMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// OptionsMessage
	bool OptionsMessage::is_valid()
	{std::cout << "OptionsMessage::is_valid\n";
		return_false_if_true(!Base::is_valid())
		return true;
	}

	// ReferMessage
	bool ReferMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return_false_if_true(contact_ == 0)
		return_false_if_true(refer_to_ == 0)

		return true;
	}
	// SubscribeMessage
	bool SubscribeMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return_false_if_true(contact_ == 0)
		return_false_if_true(event_ == 0)
		return_false_if_true(allow_events_ == 0)

		return true;
	}
	// NotifyMessage
	bool NotifyMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return_false_if_true(contact_ == 0)
		return_false_if_true(event_ == 0)
		return_false_if_true(allow_events_ == 0)
		return_false_if_true(subscription_state_ == 0)

		return true;
	}
	// MessageMessage
	bool MessageMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// InfoMessage
	bool InfoMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// PrackMessage
	bool PrackMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return true;
	}
	// UpdateMessage
	bool UpdateMessage::is_valid()
	{
		return_false_if_true(!Base::is_valid())
		return_false_if_true(contact_ == 0)

		return true;
	}

	ResponseMessage& ResponseMessage::create()
	{
		Base::create();
		std::ostringstream o;

		o << *resp_status_ << '\n';
		o << *this;

		msg_ = o.str();

		return *this;
	}

	void ResponseMessage::parse(size_t &pos)
	{
		if (msg_.empty()) return;

		resp_status_->parse(msg_, pos);
		Base::parse(pos);
		
		std::cout << "-resonse------------------------\n";
		std::cout << *resp_status_ << '\n';
		std::cout << *this;
		std::cout << "--------------------------------\n";
	}
} // namespace EasySip
