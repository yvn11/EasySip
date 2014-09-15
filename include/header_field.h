/*
 * include/header_field.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 *
 * References:
 * 		Session Initiation Protocol (Sip) Parameters, IANA
 * 		RFC-3261
 * 		RFC-6665
 *		SIP, Understanding The Session Initiation Protocol, 2nd Ed, Artech House
 */
#pragma once

#include "uri.h"
#include "response_code.h"
#include "request_message.h"
#include <iostream>

namespace EasySip
{
	#define SIP_VERSION_1_0 "SIP/1.0"
	#define SIP_VERSION_2_0 "SIP/2.0"
	#define SIP_VERSION_2_0_UDP SIP_VERSION_2_0"/UDP"
	#define SIP_VERSION SIP_VERSION_2_0

	struct HeaderField
	{
		std::string field_;
		std::string compact_form_;
		std::string values_;
		HeaderParams header_params_;
		bool is_hop_by_hop_;

		HeaderField(std::string f, bool is_hbh = false)
		: field_(f), is_hop_by_hop_(is_hbh)
		{
		}

		HeaderField(std::string f, std::string c, bool is_hbh = false)
		: field_(f), compact_form_(c), is_hop_by_hop_(is_hbh)
		{
		}
	
		HeaderField()
		{
		}

		~HeaderField()
		{
		}

		std::string Compact()
		{
			return compact_form_;
		}

		std::string Field()
		{
			return field_;
		}

		bool is_value_valid()
		{
			return true;
		}

		virtual void generate_values()
		{
			std::cout << __PRETTY_FUNCTION__ << '\n';
		}

		virtual void parse(std::string &msg, size_t &pos)
		{
			std::cout << __PRETTY_FUNCTION__ << '\n';
		}

		std::string Values()
		{
			return values_;
		}

		void HeaderParam(std::string n, std::string v)
		{
			header_params_.set_value_by_name(n, v);
		}

		friend std::ostream& operator<< (std::ostream& o, HeaderField& hf);

		std::string operator() ();
	};

	// ---------- Mandatory fields ---------------
	/* Call-ID: 19283kjhj5h
	 */
	struct HFCallId : public HeaderField
	{
		std::string id_;

		HFCallId() : HeaderField("Call-ID", "i")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* CSeq: 35246 INVITE 
	 */
	struct HFCSeq : public HeaderField
	{
		std::string cseq_;
		std::string method_;

		HFCSeq() : HeaderField("CSeq")
		{
		}

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};
	
	struct HFBase_1_ : public HeaderField
	{
		std::string name_;
		URI uri_;

		HFBase_1_(std::string f, std::string c) : HeaderField(f, c)
		{
			header_params_.append("tag");
		}

		virtual void generate_values();
		virtual void parse(std::string &msg, size_t &pos);

	};
	/* From: Alice <sip:alice@atlanta.com>;tag=87263237
	 */
	struct HFFrom : public HFBase_1_
	{
		HFFrom() : HFBase_1_("From", "f")
		{
		}
	};

	/* To: Alice <sip:alice@atlanta.com>;tag=39u292sd7
	 */
	struct HFTo : public HFBase_1_
	{
		HFTo() : HFBase_1_("To", "t")
		{
		}
	};

	/* Via: SIP/2.0/UDP <aa.atlanta.com>;branch=38Z89sdhJ;received=192.168.0.50
	 * Via: SIP/2.0/UDP <cc.atlanta.com>;branch=2998H933k;received=192.168.0.43
	 * Via: SIP/2.0/UDP 135.180.130.133
	 * ...
	 */
	struct HFVia : public HeaderField
	{
		std::string sent_proto_;
		std::string sent_by_;

		HFVia();

//		std::string version()
//		{
//			return proto_.substr(proto_.find_last_of("/"));
//		}
//
//		std::string transmit_protocol()
//		{
//			return proto_.substr(proto_.find_last_of("/")+1);
//		}

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	// ------------------ Optional fields --------------------

	/* Alert-Info: <http://wwww.example.com/alice/photo.jpg> ;purpose=icon,
     *		<http://www.example.com/alice/> ;purpose=info
	 */
	struct HFAlertInfo : public HeaderField
	{
		HFAlertInfo() : HeaderField("Alert-Info", true)
		{
			header_params_.append("appearance");
			header_params_.append("purpose");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAllowEvents : public HeaderField
	{
		HFAllowEvents() : HeaderField("Allow-Events", "u")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFDate : public HeaderField
	{
		HFDate() : HeaderField("Date", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* Contact: <sip:user@example.com?Route=%3Csip:sip.example.com%3E>
	 */
	struct HFContact : public HeaderField
	{
		URI uri_;

		HFContact();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFOrganization : public HeaderField
	{
		HFOrganization() : HeaderField("Organization", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* Record-Route: <sip:+1-650-555-2222@iftgw.there.com;
	 * 		maddr=ss1.wcom.com>
	 * Record-Route: <sip:139.23.1.44;lr>
	 */
	struct HFRecordRoute : public HeaderField
	{
		HFRecordRoute() : HeaderField("Record-Route", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRetryAfter : public HeaderField
	{
		HFRetryAfter() : HeaderField("Retry-After")
		{
			header_params_.append("duration");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFSubject : public HeaderField
	{
		HFSubject() : HeaderField("Subject", "s")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFSupported : public HeaderField
	{
		HFSupported() : HeaderField("Supported", "k")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFTimestamp : public HeaderField
	{
		HFTimestamp() : HeaderField("Timestamp")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFUserAgent : public HeaderField
	{
		HFUserAgent() : HeaderField("User-Agent")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAnswerMode : public HeaderField
	{
		HFAnswerMode() : HeaderField("Answer-Mode")
		{
			header_params_.append("require");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPrivAnswerMode : public HeaderField
	{
		HFPrivAnswerMode() : HeaderField("Priv-Answer-Mode")
		{
			header_params_.append("require");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	// -------------------- Request header -----------------------------
	struct HFAccept : public HeaderField
	{
		HFAccept() : HeaderField("Accept") // type/sub-type
		{
			header_params_.append("q");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAcceptContact : public HeaderField
	{
		HFAcceptContact() : HeaderField("Accept-Contact", "a")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAcceptEncoding : public HeaderField
	{
		HFAcceptEncoding() : HeaderField("Accept-Encoding")
		{
			header_params_.append("q");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAcceptLanguage : public HeaderField
	{
		HFAcceptLanguage() : HeaderField("Accept-Language")
		{
			header_params_.append("q");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAuthorization : public HeaderField
	{
		HFAuthorization();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFCallInfo : public HeaderField
	{
		HFCallInfo();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFEvent : public HeaderField
	{
		HFEvent();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFInReplyTo : public HeaderField
	{
		HFInReplyTo() : HeaderField("In-Reply-To")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFJoin : public HeaderField
	{
		HFJoin() : HeaderField("Join")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPriority : public HeaderField
	{
		HFPriority() : HeaderField("Priority", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPrivacy : public HeaderField
	{
		HFPrivacy() : HeaderField("Privacy", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFProxyAuthorization : public HeaderField
	{
		HFProxyAuthorization();
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFProxyRequire : public HeaderField
	{
		HFProxyRequire() : HeaderField("Proxy-Require", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPOSPAuthToken : public HeaderField
	{
		HFPOSPAuthToken() : HeaderField("P-OSP-Auth-Token")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPAssertedIdentity : public HeaderField
	{
		HFPAssertedIdentity() : HeaderField("P-Asserted-Identity")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPPreferredIdentity : public HeaderField
	{
		HFPPreferredIdentity() : HeaderField("P-Preferred-Identity")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFMaxForwards : public HeaderField
	{
		std::string max_fw_;

		HFMaxForwards() : HeaderField("Max-Forwards", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFReason : public HeaderField
	{
		HFReason() : HeaderField("Reason", true)
		{
			header_params_.append("cause");
			header_params_.append("text");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFReferTo : public HeaderField
	{
		HFReferTo() : HeaderField("Refer-To", "r")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* Referred-By: <sip:user@host.com>
	 */
	struct HFReferredBy : public HeaderField
	{
		HFReferredBy() : HeaderField("Referred-By", "b")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFReplyTo : public HeaderField
	{
		HFReplyTo() : HeaderField("Replay-To")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFReplaces : public HeaderField
	{
		HFReplaces() : HeaderField("Replaces")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRejectContact : public HeaderField
	{
		HFRejectContact() : HeaderField("Reject-Contact", "j")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRequestDisposition : public HeaderField
	{
		HFRequestDisposition() : HeaderField("Request-Disposition")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* Require: 100rel
	 */
	struct HFRequire : public HeaderField
	{
		HFRequire() : HeaderField("Require", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRoute : public HeaderField
	{
		HFRoute() : HeaderField("Route", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRack : public HeaderField
	{
		HFRack() : HeaderField("RACK")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFSessionExpires : public HeaderField
	{
		HFSessionExpires() : HeaderField("Session-Expires", "x")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFSubscriptionState : public HeaderField
	{
		HFSubscriptionState();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	// -------------------- Response header -----------------------------
	struct HFAuthenticationInfo : public HeaderField
	{
		HFAuthenticationInfo();
		
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFErrorInfo : public HeaderField
	{
		HFErrorInfo() : HeaderField("Error-Info", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFMinExpires : public HeaderField
	{
		HFMinExpires() : HeaderField("Min-Expires")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFMinSE : public HeaderField
	{
		HFMinSE() : HeaderField("Min-SE")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFProxyAuthenticate : public HeaderField
	{
		HFProxyAuthenticate();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFServer : public HeaderField
	{
		HFServer() : HeaderField("Server")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	/* Unsupported: 100rel
	 */
	struct HFUnsupported : public HeaderField
	{
		HFUnsupported() : HeaderField("Unsupported")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFWarning : public HeaderField
	{
		std::string code_;
		std::string agent_; // hostport or pseudonym
		std::string text_;

		HFWarning() : HeaderField("Warning")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFWWWAuthenticate : public HeaderField
	{
		HFWWWAuthenticate();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFRSeq : public HeaderField
	{
		HFRSeq() : HeaderField("RSeq")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAllow : public HeaderField
	{
		HFAllow() : HeaderField("Allow")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFContentEncoding : public HeaderField
	{
		HFContentEncoding() : HeaderField("Content-Encoding", "e")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFContentLength : public HeaderField
	{
		std::string length_;

		HFContentLength() : HeaderField("Content-Length", "l", true)
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFContentLanguage : public HeaderField
	{
		HFContentLanguage() : HeaderField("Content-Language")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFContentType : public HeaderField
	{
		std::string discrete_ty_;
		std::string composite_ty_;

		HFContentType() : HeaderField("Content-Type", "c")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFExpires : public HeaderField
	{
		HFExpires() : HeaderField("Expires")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFMIMEVersion : public HeaderField
	{
		HFMIMEVersion() : HeaderField("MIME-Version")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct RequestLine
	{
		MethodMap method_;
		std::string request_uri_;
		std::string version_;

		RequestLine()
		{
		//	version_ = SIP_VERSION_2_0;
		}

		std::string operator() ()
		{
			std::ostringstream ret;
			
			ret << method_.Name() << " " << request_uri_ << " " << version_ << "\n";
			return ret.str();
		}

		friend std::ostream& operator<< (std::ostream &o, RequestLine req)
		{
			o << req.method_.Name() << " " << req.request_uri_ << " " << req.version_;
			return o;
		}

		void parse(std::string &msg, size_t &pos);
	};

	struct ResponseStatus
	{
		std::string version_;
		RespCode resp_code_; // status_code_, reason_parase_

		ResponseStatus()
		{
//			version_ = SIP_VERSION_2_0;
//			resp_code_ = SIP_RESPONSE_SUCCESSFUL;
		}

		std::string operator() ()
		{
			std::ostringstream ret;

			ret << version_ << " " << resp_code_ << "\n";
			return ret.str();
		}

		friend std::ostream& operator<< (std::ostream &o, ResponseStatus res)
		{
			o << res.version_ << " " << res.resp_code_;
			return o;
		}

		void parse(std::string &msg, size_t &pos);

		ResponseStatus& operator=(ResponseStatus resp)
		{
			version_ = resp.version_;
			resp_code_ = resp.resp_code_;
			return *this;
		}
	};

	#define out_if_not_null(o, hf) { if (hf) o << *hf; }
	#define out_if_not_empty(o, hf) {		\
		for o << hf;		\
	}

	struct HeaderFields
	{
		typedef std::vector<std::string> T_HF_MAP;

		std::shared_ptr<RequestLine> req_line_;
		std::shared_ptr<ResponseStatus> resp_status_;
		// mandatory
		std::shared_ptr<HFCallId> call_id_;
		std::shared_ptr<HFCSeq> cseq_;
		std::shared_ptr<HFFrom> from_;
		std::shared_ptr<HFTo> to_;
		std::vector<std::shared_ptr<HFVia> > via_;
		// Optional
		std::shared_ptr<HFAlertInfo> alert_info_;
		std::shared_ptr<HFAllowEvents> allow_events_;
		std::shared_ptr<HFDate> date_;
		std::shared_ptr<HFContact> contact_;
		std::shared_ptr<HFOrganization> organization_;
		std::shared_ptr<HFRecordRoute> record_route_;
		std::shared_ptr<HFRetryAfter> retry_after_; // in second
		std::shared_ptr<HFSubject> subject_;
		std::shared_ptr<HFSupported> supported_;
		std::shared_ptr<HFTimestamp> timestamp_;
		std::shared_ptr<HFUserAgent> user_agent_;
		std::shared_ptr<HFAnswerMode> answer_mode_;
		std::shared_ptr<HFPrivAnswerMode> priv_answer_mode_;
		// request header fields
		std::shared_ptr<HFAccept> accept_; // type/sub-type
		std::shared_ptr<HFAcceptContact> accept_contact_;
		std::shared_ptr<HFAcceptEncoding> accept_encoding_;
		std::shared_ptr<HFAcceptLanguage> accept_language_;
		std::shared_ptr<HFAuthorization> authorization_;
		std::shared_ptr<HFCallInfo> call_info_;
		std::shared_ptr<HFEvent> event_;
		std::shared_ptr<HFInReplyTo> in_replay_to_;
		std::shared_ptr<HFJoin> join_;
		std::shared_ptr<HFPriority> priority_;
		std::shared_ptr<HFPrivacy> privacy_;
		std::shared_ptr<HFProxyAuthorization> proxy_authorization_;
		std::shared_ptr<HFProxyRequire> proxy_require_;
		std::shared_ptr<HFPOSPAuthToken> p_osp_auth_token_;
		std::shared_ptr<HFPAssertedIdentity> p_asserted_identity_;
		std::shared_ptr<HFPPreferredIdentity> p_preferred_identity_;
		std::shared_ptr<HFMaxForwards> max_forwards_;
		std::shared_ptr<HFReason> reason_;
		std::shared_ptr<HFReferTo> refer_to_;
		std::shared_ptr<HFReferredBy> referred_by_;
		std::shared_ptr<HFReplyTo> reply_to_;
		std::shared_ptr<HFReplaces> replaces_;
		std::shared_ptr<HFRejectContact> reject_contact_;
		std::shared_ptr<HFRequestDisposition> request_disposition_;
		std::shared_ptr<HFRequire> require_;
		std::shared_ptr<HFRoute> route_;
		std::shared_ptr<HFRack> rack_;
		std::shared_ptr<HFSessionExpires> session_expires_; // in second
		std::shared_ptr<HFSubscriptionState> subscription_state_;
		// response header fields
		std::shared_ptr<HFAuthenticationInfo> authentication_info_;
		std::shared_ptr<HFErrorInfo> error_info_;
		std::shared_ptr<HFMinExpires> min_expires_;
		std::shared_ptr<HFMinSE> min_se_;
		std::shared_ptr<HFProxyAuthenticate> proxy_authenticate_;
		std::shared_ptr<HFServer> server_;
		std::shared_ptr<HFUnsupported> unsupported_;
		std::shared_ptr<HFWarning> warning_;
		std::shared_ptr<HFWWWAuthenticate> www_authenticate_;
		std::shared_ptr<HFRSeq> rseq_;
		// message header fields
		std::shared_ptr<HFAllow> allow_;
		std::shared_ptr<HFContentEncoding> content_encoding_;
		std::shared_ptr<HFContentLength> content_length_;
		std::shared_ptr<HFContentLanguage> content_language_;
		std::shared_ptr<HFContentType> content_type_;
		std::shared_ptr<HFExpires> expires_; // in second
		std::shared_ptr<HFMIMEVersion> mime_version_;



//		// mandatory
//		HeaderFieldList<HFCallId> call_id_;
//		HeaderFieldList<HFCSeq> cseq_;
//		HeaderFieldList<HFFrom> from_;
//		HeaderFieldList<HFTo> to_;
//		HeaderFieldList<HFVia> via_;
//		// Optional
//		HeaderFieldList<HFAlertInfo> alert_info_;
//		HeaderFieldList<HFAllowEvents> allow_events_;
//		HeaderFieldList<HFDate> date_;
//		HeaderFieldList<HFContact> contact_;
//		HeaderFieldList<HFOrganization> organization_;
//		HeaderFieldList<HFRecordRoute> record_route_;
//		HeaderFieldList<HFRetryAfter> retry_after_; // in second
//		HeaderFieldList<HFSubject> subject_;
//		HeaderFieldList<HFSupported> supported_;
//		HeaderFieldList<HFTimestamp> timestamp_;
//		HeaderFieldList<HFUserAgent> user_agent_;
//		HeaderFieldList<HFAnswerMode> answer_mode_;
//		HeaderFieldList<HFPrivAnswerMode> priv_answer_mode_;
//		// request header fields
//		HeaderFieldList<HFAccept> accept_; // type/sub-type
//		HeaderFieldList<HFAcceptContact> accept_contact_;
//		HeaderFieldList<HFAcceptEncoding> accept_encoding_;
//		HeaderFieldList<HFAcceptLanguage> accept_language_;
//		HeaderFieldList<HFAuthorization> authorization_;
//		HeaderFieldList<HFCallInfo> call_info_;
//		HeaderFieldList<HFEvent> event_;
//		HeaderFieldList<HFInReplyTo> in_replay_to_;
//		HeaderFieldList<HFJoin> join_;
//		HeaderFieldList<HFPriority> priority_;
//		HeaderFieldList<HFPrivacy> privacy_;
//		HeaderFieldList<HFProxyAuthorization> proxy_authorization_;
//		HeaderFieldList<HFProxyRequire> proxy_require_;
//		HeaderFieldList<HFPOSPAuthToken> p_osp_auth_token_;
//		HeaderFieldList<HFPAssertedIdentity> p_asserted_identity_;
//		HeaderFieldList<HFPPreferredIdentity> p_preferred_identity_;
//		HeaderFieldList<HFMaxForwards> max_forwards_;
//		HeaderFieldList<HFReason> reason_;
//		HeaderFieldList<HFReferTo> refer_to_;
//		HeaderFieldList<HFReferredBy> referred_by_;
//		HeaderFieldList<HFReplyTo> reply_to_;
//		HeaderFieldList<HFReplaces> replaces_;
//		HeaderFieldList<HFRejectContact> reject_contact_;
//		HeaderFieldList<HFRequestDisposition> request_disposition_;
//		HeaderFieldList<HFRequire> require_;
//		HeaderFieldList<HFRoute> route_;
//		HeaderFieldList<HFRack> rack_;
//		HeaderFieldList<HFSessionExpires> session_expires_; // in second
//		HeaderFieldList<HFSubscriptionState> subscription_state_;
//		// response header fields
//		HeaderFieldList<HFAuthenticationInfo> authentication_info_;
//		HeaderFieldList<HFErrorInfo> error_info_;
//		HeaderFieldList<HFMinExpires> min_expires_;
//		HeaderFieldList<HFMinSE> min_se_;
//		HeaderFieldList<HFProxyAuthenticate> proxy_authenticate_;
//		HeaderFieldList<HFServer> server_;
//		HeaderFieldList<HFUnsupported> unsupported_;
//		HeaderFieldList<HFWarning> warning_;
//		HeaderFieldList<HFWWWAuthenticate> www_authenticate_;
//		HeaderFieldList<HFRSeq> rseq_;
//		// message header fields
//		HeaderFieldList<HFAllow> allow_;
//		HeaderFieldList<HFContentEncoding> content_encoding_;
//		HeaderFieldList<HFContentLength> content_length_;
//		HeaderFieldList<HFContentLanguage> content_language_;
//		HeaderFieldList<HFContentType> content_type_;
//		HeaderFieldList<HFExpires> expires_; // in second
//		HeaderFieldList<HFMIMEVersion> mime_version_;

		HeaderFields();

		~HeaderFields();

//		friend std::ostream& operator<< (std::ostream& o, HeaderFields& hf);

	protected:
		T_HF_MAP allowed_fields_;
		void init_allowed_fields();
	};

} // namespace EasySip
