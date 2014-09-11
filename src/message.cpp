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
		o << msg.call_id_;
		o << msg.cseq_;
		o << msg.from_;
		o << msg.to_;
		o << msg.via_;
		o << msg.alert_info_;
		o << msg.allow_events_;
		o << msg.date_;
		o << msg.contact_;
		o << msg.organization_;
		o << msg.record_route_;
		o << msg.retry_after_;
		o << msg.subject_;
		o << msg.supported_;
		o << msg.timestamp_;
		o << msg.user_agent_;
		o << msg.answer_mode_;
		o << msg.priv_answer_mode_;
		o << msg.accept_;
		o << msg.accept_contact_;
		o << msg.accept_encoding_;
		o << msg.accept_language_;
		o << msg.authorization_;
		o << msg.call_info_;
		o << msg.event_;
		o << msg.in_replay_to_;
		o << msg.join_;
		o << msg.priority_;
		o << msg.privacy_;
		o << msg.proxy_authorization_;
		o << msg.proxy_require_;
		o << msg.p_osp_auth_token_;
		o << msg.p_asserted_identity_;
		o << msg.p_preferred_identity_;
		o << msg.max_forwards_;
		o << msg.reason_;
		o << msg.refer_to_;
		o << msg.referred_by_;
		o << msg.reply_to_;
		o << msg.replaces_;
		o << msg.reject_contact_;
		o << msg.request_disposition_;
		o << msg.require_;
		o << msg.route_;
		o << msg.rack_;
		o << msg.session_expires_;
		o << msg.subscription_state_;
		o << msg.authentication_info_;
		o << msg.error_info_;
		o << msg.min_expires_;
		o << msg.min_se_;
		o << msg.proxy_authenticate_;
		o << msg.server_;
		o << msg.unsupported_;
		o << msg.warning_;
		o << msg.www_authenticate_;
		o << msg.rseq_;
		o << msg.allow_;
		o << msg.content_encoding_;
		o << msg.content_length_;
		o << msg.content_language_;
		o << msg.content_type_;
		o << msg.expires_;
		o << msg.mime_version_;

		o << msg.user_data_;

		return o;
	}
	Message& Message::create()
	{
		if (!is_valid())
		{	// TODO throw exception
			std::cerr << "message invalid\n";
			return RefOf<Message>(*this);
		}

		std::ostringstream o;
		o << user_data_.size();

		content_length_.append_field();
		content_length_.at(0)->length_ = o.str();//append_value(o.str());

		return RefOf<Message>(*this);
	}

	bool Message::is_valid()
	{
		if (call_id_.empty())
			return false;
		if (cseq_.empty())
			return false;
		if (from_.empty())
			return false;
		if (to_.empty())
			return false;
		if (via_.empty())
			return false;
		if (max_forwards_.empty())
			return false;

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

	/* parse buffered header into formated header fields
	 */
	void Message::parse(size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';

		if (msg_.empty())
			return;

		size_t next = pos;

		while (1)
		{
			next = msg_.find_first_of(":", pos);

			if (std::string::npos == next)
				break;

			std::string field(msg_.substr(pos, next-pos));
			std::cout << "field:: " << field << '\n';	

			if (field == HFFrom().Field())
			{
				from_.append_field();
				from_.at(0)->parse(msg_, pos);
			}

			else if (field == HFVia().Field())
			{
				via_.append_field();
				via_.at(via_.size()-1)->parse(msg_, pos);
			}
	//TODO: fields
	//		else
			{
				pos = next + 1;
			}
		}
	}

	RequestMessage& RequestMessage::create()
	{
		Base::create();
		std::ostringstream o;

		o << req_line_ << '\n';
		o << *this;

		msg_ = o.str();

		return RefOf<RequestMessage>(*this);
	}

	void RequestMessage::parse(size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';

		if (msg_.empty())
			return;

		req_line_.parse(msg_, pos);
		std::cout << "req_line: " << req_line_ << '\n';

		Base::parse(pos);
	}

	InviteMessage& InviteMessage::create()
	{
		return RefOf<InviteMessage>(*this);
	}

	void InviteMessage::parse()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';

		size_t pos = 0;
		RequestMessage::parse(pos);
	}

	bool InviteMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;

		if (contact_.empty())
			return false;

		return true;
	}
	// RegisterMessage
	RegisterMessage& RegisterMessage::create()
	{
		return RefOf<RegisterMessage>(*this);
	}

	bool RegisterMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// AckMessage
	AckMessage& AckMessage::create()
	{
		return RefOf<AckMessage>(*this);
	}

	bool AckMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// ByeMessage
	ByeMessage& ByeMessage::create()
	{
		return RefOf<ByeMessage>(*this);
	}

	bool ByeMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// CancelMessage
	CancelMessage& CancelMessage::create()
	{
		return RefOf<CancelMessage>(*this);
	}
	
	bool CancelMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// OptionsMessage
	OptionsMessage& OptionsMessage::create()
	{
		return RefOf<OptionsMessage>(*this);
	}

	bool OptionsMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}

	// ReferMessage
	ReferMessage& ReferMessage::create()
	{
		return RefOf<ReferMessage>(*this);
	}

	bool ReferMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		if (contact_.empty())
			return false;
		if (refer_to_.empty())
			return false;

		return true;
	}
	// SubscribeMessage
	SubscribeMessage& SubscribeMessage::create()
	{
		return RefOf<SubscribeMessage>(*this);
	}

	bool SubscribeMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		if (contact_.empty())
			return false;
		if (event_.empty())
			return false;
		if (allow_events_.empty())
			return false;

		return true;
	}
	// NotifyMessage
	NotifyMessage& NotifyMessage::create()
	{
		return RefOf<NotifyMessage>(*this);
	}

	bool NotifyMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		if (contact_.empty())
			return false;
		if (event_.empty())
			return false;
		if (allow_events_.empty())
			return false;
		if (subscription_state_.empty())
			return false;

		return true;
	}
	// MessageMessage
	MessageMessage& MessageMessage::create()
	{
		return RefOf<MessageMessage>(*this);
	}

	bool MessageMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// InfoMessage
	InfoMessage& InfoMessage::create()
	{
		return RefOf<InfoMessage>(*this);
	}

	bool InfoMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// PrackMessage
	PrackMessage& PrackMessage::create()
	{
		return RefOf<PrackMessage>(*this);
	}

	bool PrackMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		return true;
	}
	// UpdateMessage
	UpdateMessage& UpdateMessage::create()
	{
		return RefOf<UpdateMessage>(*this);
	}

	bool UpdateMessage::is_valid()
	{
		if (!Base::is_valid())
			return false;
		if (contact_.empty())
			return false;

		return true;
	}

	ResponseMessage& ResponseMessage::create()
	{
		Base::create();
		std::ostringstream o;

		o << resp_status_ << '\n';
		o << *this;

		msg_ = o.str();

		return RefOf<ResponseMessage>(*this);
	}
} // namespace EasySip
