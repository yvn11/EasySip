/*
 * src/message.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "message.h"

namespace EasySip
{
	Message& Message::create()
	{
		content_length_.append_field();

		std::ostringstream o;
		o << msg_.size();

		content_length_.append_value(o.str());

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

	InviteMessage& InviteMessage::create()
	{
		return RefOf<InviteMessage>(*this);
	}

	void InviteMessage::parse_header()
	{
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
		return RefOf<ResponseMessage>(*this);
	}
} // namespace EasySip
