/*
 * include/method.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once
#include "message.h"

namespace EasySip
{
//	MethodMap<InviteMethod> METHOD_INVITE(METHOD_ID_INVITE, "INVITE");
//	MethodMap<CancelMethod> METHOD_CANCEL(METHOD_ID_CANCEL, "CANCEL");
//	MethodMap<AckMethod> METHOD_ACK(METHOD_ID_ACK, "ACK");
//	MethodMap<ByeMethod> METHOD_BYE(METHOD_ID_BYE, "BYE");
//	MethodMap<RegisterMethod> METHOD_REGISTER(METHOD_ID_REGISTER, "REGISTER");
//	MethodMap<OptionsMeshod> METHOD_OPTIONS(METHOD_ID_OPTIONS, "OPTIONS");
//	// Additional requests since SIP 2.0
//	// RFC-6665
//	MethodMap<SubscribeMethod> METHOD_SUBSCRIBE(METHOD_ID_SUBSCRIBE, "SUBSCRIBE");
//	MethodMap<NotifyMethod> METHOD_NOTIFY(METHOD_ID_NOTIFY, "NOTIFY");
//	MethodMap<MessageMethod> METHOD_MESSAGE(METHOD_ID_MESSAGE, "MESSAGE");
//	// RFC-6086
//	MethodMap<InfoMethod> METHOD_INFO(METHOD_ID_INFO, "INFO");
//	// RFC-3311
//	MethodMap<UpdateMethod> METHOD_UPDATE(METHOD_ID_UPDATE, "UPDATE");
//	// RFC-3515
//	MethodMap<ReferMethod> METHOD_REFER(METHOD_ID_REFER, "REFER");
//	// RFC-3262
//	MethodMap<PrackMethod> METHOD_PRACK(METHOD_ID_PRACK, "PRACK");

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
			//msg_ = std::make_shared<InviteMessage>();
			//msg_->req_line_.method_ = METHOD_INVITE.Name();
		}

		InviteMethod(RequestMessage &in_msg)
		{
			msg_ = std::make_shared<InviteMessage>(in_msg);
		}

		InviteMethod(std::string in_msg)
		{
			msg_ = std::make_shared<InviteMessage>(in_msg);
		}

		~InviteMethod()
		{
		}

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
