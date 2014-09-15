/*
 * include/message.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "header_field.h"
#include "request_message.h"
#include <iostream>

namespace EasySip
{
	/*
	 * Mandatory fields:
	 * Call-ID
	 * CSeq
	 * From
	 * To
	 * Via
	 * Max-Forwards
	*/
	class Message : public HeaderFields
	{
	protected:
		typedef Message Base;
		std::string user_data_;
		std::string msg_; // message to send or received, which contains header fields and user data

	public:

		Message()
		{
		}

		Message(std::string msg)
		: msg_(msg)
		{
		}

		std::string Msg()
		{
			return msg_;
		}

//		void Msg(std::string msg)
//		{
//			msg_ = msg;
//		}

		~Message()
		{
		}

		MethodMap method()
		{
			return req_line_->method_;
		}

		void append_userdata(std::string buf)
		{
			user_data_.append(buf);
		}

		virtual Message& create();
		virtual bool is_valid();
		/* parse buffered header into formated header fields
		 */
		virtual void parse(size_t &pos);

		template<typename T>
		void parse_dispatch_if_match(
			std::shared_ptr<T> &f, std::string buf,
			std::string &msg, size_t &pos)
		{
			if (T().Field() == buf || T().Compact() == buf)
			{
				 f = std::make_shared<T>();
				 f->parse(msg, pos);
			}
		}
		
		virtual void parse_dispatch(std::string field, size_t &pos);

		static int get_method_from_buffer(
			MethodMapList &allowed_methods, std::string msg, std::string sym = " ");

		static int get_response_code_from_buffer(
			RespCodeList &allowed_responses, std::string msg, std::string sym = " ");

		static std::vector<std::string> split_by(std::string msg, std::string sym = " ");

		friend std::ostream& operator<< (std::ostream& o, Message& hf);
	};
	
	// ---------------- Request messages --------------------------
	class RequestMessage : public Message
	{
	public:
		RequestMessage()
		{
			req_line_ = std::make_shared<RequestLine>();
		}

		RequestMessage(std::string &in_msg)
		{
			req_line_ = std::make_shared<RequestLine>();
			msg_ = in_msg;
		}

		RequestMessage(RequestMessage &in_msg)
		{
			req_line_ = std::make_shared<RequestLine>();
			*this = in_msg;
		}

		RequestMessage& create();

		virtual void parse(size_t &pos);
		virtual void parse()
		{
			size_t pos = 0;
			parse(pos);
		}
	};

	class InviteMessage : public RequestMessage
	{
	public:

		InviteMessage()
		{
			req_line_->method_ = METHOD_INVITE;
		}

		InviteMessage(std::string &in_msg)
		{
			req_line_->method_ = METHOD_INVITE;
			msg_ = in_msg;
		}

		InviteMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_INVITE;
		}

		~InviteMessage()
		{
		}

		InviteMessage& create();
		bool is_valid();
		void parse();
	};

	class RegisterMessage : public RequestMessage
	{
	public:
		RegisterMessage()
		{
			req_line_->method_ = METHOD_REGISTER;
		}

		RegisterMessage(std::string &in_msg)
		{
			req_line_->method_ = METHOD_REGISTER;
			msg_ = in_msg;
		}

		RegisterMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_REGISTER;
		}

		~RegisterMessage()
		{
		}

		RegisterMessage& create();
		bool is_valid();
	};

	class ByeMessage : public RequestMessage
	{
	public:
		ByeMessage()
		{
			req_line_->method_ = METHOD_BYE;
		}

		~ByeMessage()
		{
		}

		ByeMessage& create();
		bool is_valid();
	};

	class AckMessage : public RequestMessage
	{
	public:
		AckMessage()
		{
			req_line_->method_ = METHOD_ACK;
		}

		~AckMessage()
		{
		}

		AckMessage& create();
		bool is_valid();
	};

	class CancelMessage : public RequestMessage
	{
	public:
		CancelMessage()
		{
			req_line_->method_ = METHOD_CANCEL;
		}

		~CancelMessage()
		{
		}

		CancelMessage& create();
		bool is_valid();
	};

	class OptionsMessage : public RequestMessage
	{
	public:
		OptionsMessage()
		{
			req_line_->method_ = METHOD_OPTIONS;
		}

		~OptionsMessage()
		{
		}

		OptionsMessage& create();
		bool is_valid();
	};

	class ReferMessage : public RequestMessage
	{
	public:
		ReferMessage()
		{
			req_line_->method_ = METHOD_REFER;
		}

		~ReferMessage()
		{
		}

		ReferMessage& create();
		bool is_valid();
	};

	class SubscribeMessage : public RequestMessage
	{
	public:
		SubscribeMessage()
		{
			req_line_->method_ = METHOD_SUBSCRIBE;
		}

		~SubscribeMessage()
		{
		}

		SubscribeMessage& create();
		bool is_valid();
	};

	class NotifyMessage : public RequestMessage
	{
	public:
		NotifyMessage()
		{
			req_line_->method_ = METHOD_NOTIFY;
		}

		~NotifyMessage()
		{
		}

		NotifyMessage& create();
		bool is_valid();
	};

	class MessageMessage : public RequestMessage
	{
	public:
		MessageMessage()
		{
			req_line_->method_ = METHOD_MESSAGE;
		}

		~MessageMessage()
		{
		}

		MessageMessage& create();
		bool is_valid();
	};

	class InfoMessage : public RequestMessage
	{
	public:
		InfoMessage()
		{
			req_line_->method_ = METHOD_INFO;
		}

		~InfoMessage()
		{
		}

		InfoMessage& create();
		bool is_valid();
	};

	class PrackMessage : public RequestMessage
	{
	public:
		PrackMessage()
		{
			req_line_->method_ = METHOD_PRACK;
		}

		~PrackMessage()
		{
		}

		PrackMessage& create();
		bool is_valid();
	};

	class UpdateMessage : public RequestMessage
	{
	public:
		UpdateMessage()
		{
			req_line_->method_ = METHOD_UPDATE;
		}

		~UpdateMessage()
		{
		}

		UpdateMessage& create();
		bool is_valid();
	};

	// ---------------- Response messages --------------------------
	class ResponseMessage : public Message
	{
		
	public:
		ResponseMessage()
		{
			resp_status_ = std::make_shared<ResponseStatus>();
		}

		ResponseMessage(std::string &msg)
		{
			resp_status_ = std::make_shared<ResponseStatus>();
			msg_ = msg;
		}

		ResponseMessage(const RespCode &resp)
		{
			resp_status_ = std::make_shared<ResponseStatus>();
			resp_status_->resp_code_ = resp;

			call_id_ = std::make_shared<HFCallId>();
			cseq_ = std::make_shared<HFCSeq>();
			from_ = std::make_shared<HFFrom>();
			to_ = std::make_shared<HFTo>();
			via_.push_back(std::make_shared<HFVia>());
			max_forwards_ = std::make_shared<HFMaxForwards>();
		}

		ResponseMessage(RequestMessage &in_msg)
		{
			resp_status_ = std::make_shared<ResponseStatus>();

			call_id_ = in_msg.call_id_;
			to_ = in_msg.to_;
			from_ = in_msg.from_;
			cseq_ = in_msg.cseq_;

			via_ = in_msg.via_;
			// TODO: append via_;
		}

		~ResponseMessage()
		{
		}

		ResponseStatus& RespStatus()
		{
			return *resp_status_;
		}

		void ResponseCode(const RespCode& resp)
		{
			resp_status_->resp_code_ = resp;
		}

		RespCode& ResponseCode()
		{
			return resp_status_->resp_code_;
		}

		void ResponseVer(std::string ver)
		{
			resp_status_->version_ = ver;
		}

		std::string& ResponseVer()
		{
			return resp_status_->version_;
		}

		ResponseMessage& create();
		void parse();
	};
} // namespace EasySip
