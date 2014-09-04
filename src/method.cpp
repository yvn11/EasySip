#include "method.h"

namespace EasySip
{
	// Basic Method
	int Method::prepare(std::string dest)
	{
		msg_->req_line_.request_uri_ = dest;
		return 0;
	}

	int Method::append_header(std::string key, std::string value)
	{
//		msg_->append_header(key, value);
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

	// Invite
	void InviteMethod::parse_header()
	{
		msg_->parse_header();
	}

	int InviteMethod::on_message_receive(Message &in_msg)
	{
		return 0;
	}
} // namespace EasySip
