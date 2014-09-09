/*
 * include/message.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "header_field.h"
#include "request_message.h"

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

		~Message()
		{
		}

		MethodMap method()
		{
			return req_line_.method_;
		}

		void append_userdata(std::string buf)
		{
			user_data_.append(buf);
		}

		virtual Message& create();
		virtual bool is_valid();
//		virtual void parse_header();
	};
	
	// ---------------- Request messages --------------------------
	class RequestMessage : public Message
	{
	public:
		RequestMessage()
		{
		}

		RequestMessage(std::string &in_msg)
		{
			msg_ = in_msg;
		}

		RequestMessage(RequestMessage &in_msg)
		{
			*this = in_msg;
		}

		/* parse buffered header into formated header fields
		 */
		virtual void parse_header()
		{
			size_t pos = 0;
			// read method
			pos = msg_.find_first_of(" ", pos);
			req_line_.method_.Name(msg_.substr(pos, msg_.find_first_of(" ", pos)));
			// read request-uri
			pos = msg_.find_first_of(" ", pos);
			req_line_.request_uri_ = msg_.substr(pos+1, msg_.find_first_of(" ", pos));
			// read version
			pos = msg_.find_first_of(" ", pos);
			req_line_.version_ = msg_.substr(pos+1, msg_.find_first_of(" ", pos));

			std::string field;

			while (pos != msg_.size()-1)
			{
				pos = msg_.find_first_of("\n", pos);
				pos++;
				// read field
				size_t pos_end = msg_.find_first_of(":", pos);
				field = msg_.substr(pos, pos_end);
				pos = pos_end;

				if (allowed_fields_.find(field) == allowed_fields_.end())
					continue; // TODO: just ignore??

				
			}
		}
	};

	class InviteMessage : public RequestMessage
	{
	public:

		InviteMessage()
		{
			req_line_.method_ = METHOD_INVITE;
		}

		InviteMessage(std::string &in_msg)
		{
			msg_ = in_msg;
		}

		InviteMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
		}

		~InviteMessage()
		{
		}

		void parse_header();

		InviteMessage& create();
		bool is_valid();
	};

	class RegisterMessage : public RequestMessage
	{
	public:
		RegisterMessage()
		{
			req_line_.method_ = METHOD_REGISTER;
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
			req_line_.method_ = METHOD_BYE;
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
			req_line_.method_ = METHOD_ACK;
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
			req_line_.method_ = METHOD_CANCEL;
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
			req_line_.method_ = METHOD_OPTIONS;
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
			req_line_.method_ = METHOD_REFER;
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
			req_line_.method_ = METHOD_SUBSCRIBE;
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
			req_line_.method_ = METHOD_NOTIFY;
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
			req_line_.method_ = METHOD_MESSAGE;
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
			req_line_.method_ = METHOD_INFO;
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
			req_line_.method_ = METHOD_PRACK;
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
			req_line_.method_ = METHOD_UPDATE;
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
		}

		ResponseMessage(RespCode &resp)
		{
			RespStatus(resp);
		}

		ResponseMessage(RequestMessage &in_msg)
		{
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

		void RespStatus(ResponseStatus &resp)
		{
			resp_status_ = resp;
		}

		void RespStatus(const RespCode &resp)
		{
			resp_status_.resp_code_ = resp;
		}

		ResponseStatus& RespStatus()
		{
			return RefOf<ResponseStatus>(resp_status_);
		}

		ResponseMessage& create();
	};
} // namespace EasySip
