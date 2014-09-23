/*
 * include/message.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "header_field.h"

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

		typedef Message Ancestor;

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

		virtual void parse(size_t &pos);

		#define parse_field(f, msg, pos) \
		{ \
			f.last()->parse(msg, pos); \
		}

		virtual void parse_dispatch(std::string field, size_t &pos);

		static int get_method_from_buffer(
			MethodMapList &allowed_methods, std::string msg, std::string sym = " ");

		static int get_response_code_from_buffer(
			RespCodeList &allowed_responses, std::string msg, std::string sym = " ");

		static std::vector<std::string> split_by(std::string msg, std::string sym = " ");

		friend std::ostream& operator<< (std::ostream& o, Message& hf);


		// shotcut for each header field
	 	HFCallId* add_call_id();
	 	HFCSeq* add_cseq();
	 	HFFrom* add_from();
	 	HFTo* add_to();
	 	HFVia* add_via();
	 	HFAlertInfo* add_alert_info();
	 	HFAllowEvents* add_allow_events();
	 	HFDate* add_date();
	 	HFContact* add_contact();
	 	HFOrganization* add_organization();
	 	HFRecordRoute* add_record_route();
	 	HFRetryAfter* add_retry_after();
	 	HFSubject* add_subject();
	 	HFSupported* add_supported();
	 	HFTimestamp* add_timestamp();
	 	HFUserAgent* add_user_agent();
	 	HFAnswerMode* add_answer_mode();
	 	HFPrivAnswerMode* add_priv_answer_mode();
	 	HFAccept* add_accept();
	 	HFAcceptContact* add_accept_contact();
	 	HFAcceptEncoding* add_accept_encoding();
	 	HFAcceptLanguage* add_accept_language();
	 	HFAuthorization* add_authorization();
	 	HFCallInfo* add_call_info();
	 	HFEvent* add_event();
	 	HFInReplyTo* add_in_replay_to();
	 	HFJoin* add_join();
	 	HFPriority* add_priority();
	 	HFPrivacy* add_privacy();
	 	HFProxyAuthorization* add_proxy_authorization();
	 	HFProxyRequire* add_proxy_require();
	 	HFPOSPAuthToken* add_p_osp_auth_token();
	 	HFPAssertedIdentity* add_p_asserted_identity();
	 	HFPPreferredIdentity* add_p_preferred_identity();
	 	HFMaxForwards* add_max_forwards();
	 	HFReason* add_reason();
	 	HFReferTo* add_refer_to();
	 	HFReferredBy* add_referred_by();
	 	HFReplyTo* add_reply_to();
	 	HFReplaces* add_replaces();
	 	HFRejectContact* add_reject_contact();
	 	HFRequestDisposition* add_request_disposition();
	 	HFRequire* add_require();
	 	HFRoute* add_route();
	 	HFRack* add_rack();
	 	HFSessionExpires* add_session_expires();
	 	HFSubscriptionState* add_subscription_state();
	 	HFAuthenticationInfo* add_authentication_info();
	 	HFErrorInfo* add_error_info();
	 	HFMinExpires* add_min_expires();
	 	HFMinSE* add_min_se();
	 	HFProxyAuthenticate* add_proxy_authenticate();
	 	HFServer* add_server();
	 	HFUnsupported* add_unsupported();
	 	HFWarning* add_warning();
	 	HFWWWAuthenticate* add_www_authenticate();
	 	HFRSeq* add_rseq();
	 	HFAllow* add_allow();
	 	HFContentEncoding* add_content_encoding();
	 	HFContentLength* add_content_length();
	 	HFContentLanguage* add_content_language();
	 	HFContentType* add_content_type();
	 	HFExpires* add_expires();
	 	HFMIMEVersion* add_mime_version();
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

		void SipVersion(std::string ver)
		{
			req_line_->version_ = ver;
		}

		std::string SipVersion()
		{
			return req_line_->version_;
		}

		void RequestURI(std::string ver)
		{
			req_line_->request_uri_ = ver;
		}

		std::string RequestURI()
		{
			return req_line_->request_uri_;
		}
	
		std::string Method()
		{
			return req_line_->method_.name();
		}
	};

	class InviteMessage : public RequestMessage
	{
	public:

		InviteMessage()
		: RequestMessage()
		{
			req_line_->method_ = METHOD_INVITE;
		}

		InviteMessage(std::string &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_INVITE;
		}

		InviteMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_INVITE;
		}

		~InviteMessage()
		{
		}

		bool is_valid();
	};

	class RegisterMessage : public RequestMessage
	{
	public:
		RegisterMessage()
		: RequestMessage()
		{
			req_line_->method_ = METHOD_REGISTER;
		}

		RegisterMessage(std::string &in_msg)
		: RequestMessage(in_msg)
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

		bool is_valid();
	};

	class ByeMessage : public RequestMessage
	{
	public:
		ByeMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_BYE;
		}

		ByeMessage(std::string &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_BYE;
		}

		ByeMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_BYE;
		}

		~ByeMessage()
		{
		}

		bool is_valid();
	};

	class AckMessage : public RequestMessage
	{
	public:
		AckMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_ACK;
		}

		AckMessage(std::string &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_ACK;
		}

		AckMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_ACK;
		}

		~AckMessage()
		{
		}

		bool is_valid();
	};

	class CancelMessage : public RequestMessage
	{
	public:
		CancelMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_CANCEL;
		}

		CancelMessage(std::string &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_CANCEL;
		}

		CancelMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_CANCEL;
		}

		~CancelMessage()
		{
		}

		bool is_valid();
	};

	class OptionsMessage : public RequestMessage
	{
	public:
		OptionsMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_OPTIONS;
		}

		OptionsMessage(std::string &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_OPTIONS;
		}

		OptionsMessage(RequestMessage &in_msg)
		: RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_OPTIONS;
		}

		~OptionsMessage()
		{
		}

		bool is_valid();
	};

	class ReferMessage : public RequestMessage
	{
	public:
		ReferMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_REFER;
		}

		ReferMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_REFER;
		}

		ReferMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_REFER;
		}

		~ReferMessage()
		{
		}

		bool is_valid();
	};

	class SubscribeMessage : public RequestMessage
	{
	public:
		SubscribeMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_SUBSCRIBE;
		}

		SubscribeMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_SUBSCRIBE;
		}

		SubscribeMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_SUBSCRIBE;
		}

		~SubscribeMessage()
		{
		}

		bool is_valid();
	};

	class NotifyMessage : public RequestMessage
	{
	public:
		NotifyMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_NOTIFY;
		}

		NotifyMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_NOTIFY;
		}

		NotifyMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_NOTIFY;
		}

		~NotifyMessage()
		{
		}

		bool is_valid();
	};

	class MessageMessage : public RequestMessage
	{
	public:
		MessageMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_MESSAGE;
		}

		MessageMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_MESSAGE;
		}

		MessageMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_MESSAGE;
		}

		~MessageMessage()
		{
		}

		bool is_valid();
	};

	class InfoMessage : public RequestMessage
	{
	public:
		InfoMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_INFO;
		}

		InfoMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_INFO;
		}

		InfoMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_INFO;
		}

		~InfoMessage()
		{
		}

		bool is_valid();
	};

	class PrackMessage : public RequestMessage
	{
	public:
		PrackMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_PRACK;
		}

		PrackMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_PRACK;
		}

		PrackMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_PRACK;
		}

		~PrackMessage()
		{
		}

		bool is_valid();
	};

	class UpdateMessage : public RequestMessage
	{
	public:
		UpdateMessage() : RequestMessage()
		{
			req_line_->method_ = METHOD_UPDATE;
		}

		UpdateMessage(std::string &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_UPDATE;
		}

		UpdateMessage(RequestMessage &in_msg) : RequestMessage(in_msg)
		{
			req_line_->method_ = METHOD_UPDATE;
		}

		~UpdateMessage()
		{
		}

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
		}

		ResponseMessage(RequestMessage &in_msg)
		{
			resp_status_ = std::make_shared<ResponseStatus>();

			add_call_id()
			->add_id(in_msg.call_id_.last()->id_);

			add_from()
			->add_name(in_msg.from_.last()->name())
			.add_uri(in_msg.from_.last()->uri());

			for (auto &it : in_msg.from_.last()->header_params_)
			{
				from_.last()->HeaderParam(it.name(), it.value());
			}

			add_to()
			->add_name(in_msg.to_.last()->name())
			.add_uri(in_msg.to_.last()->uri());
	
			for (auto &it : in_msg.to_.last()->header_params_)
			{
				to_.last()->HeaderParam(it.name(), it.value());
			}

			add_cseq()
			->add_seq(in_msg.cseq_.last()->cseq_)
			.add_method(in_msg.cseq_.last()->method_)
			.inc_seq();
	
			add_via()
			->add_proto(SIP_VERSION_2_0_UDP)
			.add_sentby(in_msg.via_.last()->sent_by_);

			for (auto &it : in_msg.via_.last()->header_params_)
			{
				via_.last()->HeaderParam(it.name(), it.value());
			}
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

		void SipVersion(std::string ver)
		{
			resp_status_->version_ = ver;
		}

		std::string& SipVersion()
		{
			return resp_status_->version_;
		}

		virtual ResponseMessage& create();

		virtual void parse(size_t &pos);

		virtual void parse()
		{
			size_t pos = 0;
			parse(pos);
		}

	};

//	class MessageQueue : public std::queue<Message>
//	{
//	public:
//		void append(Message &msg)
//		{
//		}
//
//		void append(RequestMessage &msg)
//		{
//		}
//
//		void append(ResponseMessage &msg)
//		{
//		}
//	};
} // namespace EasySip
