/*
 * src/method.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "method.h"

namespace EasySip
{
	// Basic Method
	int Method::append_header(std::string key, std::string value)
	{
		if (HFFrom().Field() == key)
		{
			EasySip::append_header<HFFrom>(msg_->from_, value);
		}
		else if (HFTo().Field() == key)
		{
			EasySip::append_header<HFTo>(msg_->to_, value);
			msg_->req_line_.request_uri_ = value;
		}
		else if (HFCallId().Field() == key)
		{
			EasySip::append_header<HFCallId>(msg_->call_id_, value);
		}
		else if (HFCSeq().Field() == key)
		{
			EasySip::append_header<HFCSeq>(msg_->cseq_, value);
		}
		else if (HFVia().Field() == key)
		{
			EasySip::append_header<HFVia>(msg_->via_, value);
		}
		else
		{
			//TODO: throw exception
		}

		return 0;
	}

	int Method::append_data(std::string buf)
	{
		msg_->append_userdata(buf);
		return 0;
	}

	int Method::on_message_receive(Message &in_msg)
	{
		return 0;
	}

	int Method::send_message()
	{
		return 0;
	}

	void Method::parse_header()
	{
	}

	// Invite
	void InviteMethod::parse_header()
	{
//		msg_->parse_header();
	}

	int InviteMethod::on_message_receive(Message &in_msg)
	{
		return 0;
	}
} // namespace EasySip
