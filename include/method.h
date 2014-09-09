/*
 * include/method.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once
#include "message.h"

namespace EasySip
{
//	template<typename T>
	class Method
	{
	protected:

		std::shared_ptr<Message> msg_;

	public:
		Method()
		{
		}

		~Method()
		{
		}

		virtual void parse_header();
		virtual int append_header(std::string key, std::string value);
		virtual int append_data(std::string buf);
		virtual int send_message();
		virtual int on_message_receive(Message &in_msg);// = 0;
	};

	class InviteMethod : public Method
	{
	public:

		InviteMethod()
		{
			msg_ = std::make_shared<InviteMessage>();
			msg_->req_line_.method_ = METHOD_INVITE;
		}

		InviteMethod(RequestMessage &in_msg)
		{
			msg_ = std::make_shared<InviteMessage>(in_msg);
//			msg_->req_line_.method_ = METHOD_INVITE;
		}

		InviteMethod(std::string in_msg)
		{
			msg_ = std::make_shared<InviteMessage>(in_msg);
		}

		~InviteMethod()
		{
		}

		void parse_header();
//		int append_header(std::string key, std::string value);
		int on_message_receive(Message &in_msg);
	};

	class RegisterMethod : public Method
	{
	public:
		RegisterMethod()
		{
//			msg_ = std::make_shared<RegisterMessage>();
		}

		~RegisterMethod()
		{
		}

		int append_header(std::string key, std::string value);
		int on_message_receive(Message &in_msg);
	};

	class ByeMethod : public Method
	{
	public:
		ByeMethod()
		{
//			msg_ = std::make_shared<ByeMessage>();
		}

		~ByeMethod()
		{
		}

		int append_header(std::string key, std::string value);
		int on_message_receive(Message &in_msg);
	};

	class CancelMethod : public Method
	{
	public:
		CancelMethod()
		{
//			msg_ = std::make_shared<CancelMessage>();
		}

		~CancelMethod()
		{
		}

		int append_header(std::string key, std::string value);
		int on_message_receive(Message &in_msg);
	};

	class AckMethod : public Method
	{
	};

	class OptionsMethod : public Method
	{
	};

	class SubscribeMethod : public Method
	{
	};

	class NotifyMethod : public Method
	{
	};

	class InfoMethod : public Method
	{
	};

	class UpdateMethod : public Method
	{
	};

	class ReferMethod : public Method
	{
	};

	class MessageMethod : public Method
	{
	};

	class PrackMethod : public Method
	{
	};

	
} // namespace EasySip
