/*
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

namespace EasySip
{
#define SIP_VERSION_2_0 "SIP/2.0"

	template<typename T>
	T& RefOf(T& t) { return t; }
	
	class Param
	{
		std::string name_;
		std::string value_;
		bool has_value_;

	public:

		Param(std::string name)
		: name_(name), has_value_(true)
		{
		}

		Param(std::string name, std::string va)
		: name_(name), value_(va), has_value_(true)
		{
		}

		Param(std::string name, bool has)
		: name_(name), has_value_(has)
		{
		}

		Param(std::string name, std::string va, bool has)
		: name_(name), value_(va), has_value_(has)
		{
		}

		~Param()
		{
		}
	};

	struct HeaderField
	{
		std::string field_;
		std::string compact_form_;
		Values values_;
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

		static std::string Field()
		{
			return field_;
		}

		virtual bool is_value_valid()
		{
			return true;
		}

		friend std::ostream& operator<< (std::ostream& o, HeaderField hf)
		{
			o << hf.field_ << ": ";

			for (Values::iterator it = hf.values_.begin();
				it != hf.values_.end(); it++)
			{
				o << *it;
				
				if (std::distance(hf.values_.begin(), it) < (int)hf.values_.size())
					o << " ";
			}
			
			o << hf << "\n";

			return o;
		}

		std::string operator() ()
		{
			std::ostringstream o;
			o << *this;

			return o.str();
		}
	};
	
	typedef std::shared_ptr<HeaderField> HeaderFieldPtr;
	#define HeaderFieldPtrNew std::make_shared

	template<typename T>
	class HeaderFieldList// : public std::vector<HeaderFieldPtr>//std::shared_ptr<T> >
	{
		std::vector<std::shared_ptr<T> > hflist_;

	public:
		typedef std::shared_ptr<T> T_PTR;

		HeaderFieldList()
		{
		}

		~HeaderFieldList()
		{
		}

		void append_field()
		{
			T_PTR p = std::make_shared<T>();
			hflist_.push_back(p);
		}

		void append_value(std::string val, unsigned int index = 0)
		{
			if (index >= hflist_.size())
				return;

			hflist_.at(index)->values_.push_back(val); 
		}

		bool empty()
		{
			return hflist_.empty();
		}
	};

//	typedef std::map<std::string, HeaderField> HeaderFields;

	// ---------- Mandatory fields ---------------
	/* Call-ID: 19283kjhj5h
	 */
	struct HFCallId : public HeaderField
	{
		HFCallId() : HeaderField("Call-ID", "i")
		{
		}
	};

	/* CSeq: 35246 INVITE 
	 */
	struct HFCSeq : public HeaderField
	{
		HFCSeq() : HeaderField("CSeq")
		{
		}

//		friend std::ostream& operator<< (std::ostream& o, HFCSeq cseq)
//		{
//			o << cseq.fields_ << ": " << cseq.values_.at(0) << " " << cseq.values_.at(1) << "\n";
//			return o;
//		}
	};
	
	/* From: Alice <sip:alice@atlanta.com>;tag=87263237
	 */
	struct HFFrom : public HeaderField
	{
		HFFrom() : HeaderField("From", "f")
		{
			header_params_.append("tag");
		}
	};

	/* To: Alice <sip:alice@atlanta.com>;tag=39u292sd7
	 */
	struct HFTo : public HeaderField
	{
		HFTo() : HeaderField("To", "t")
		{
			header_params_.append("tag");
		}
	};

	/* Via: SIP/2.0/UDP aa.atlanta.com>;branch=38Z89sdhJ;received=192.168.0.50
	 * Via: SIP/2.0/UDP cc.atlanta.com>;branch=2998H933k;received=192.168.0.43
	 * Via: SIP/2.0/UDP 135.180.130.133
	 * ...
	 */
	struct HFVia : public HeaderField
	{
		HFVia() : HeaderField("Via", "v", true)
		{
			header_params_.append("alias");
			header_params_.append("branch");
			header_params_.append("comp");
			header_params_.append("keep");
			header_params_.append("maddr");
			header_params_.append("oc");
			header_params_.append("oc-algo");
			header_params_.append("oc-seq");
			header_params_.append("oc-validity");
			header_params_.append("received");
			header_params_.append("rport");
			header_params_.append("sigcomp-id");
			header_params_.append("ttl");
		}

		std::string version()
		{
			if (values_.size() > 0)
				return values_.at(0).substr(values_.at(0).find_last_of("/"));
		}

		std::string transmit_protocol()
		{
			if (values_.size() > 0)
				return values_.at(0).substr(values_.at(0).find_last_of("/")+1);
		}
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
	};

	struct HFAllowEvents : public HeaderField
	{
		HFAllowEvents() : HeaderField("Allow-Events", "u")
		{
		}
	};

	struct HFDate : public HeaderField
	{
		HFDate() : HeaderField("Date", true)
		{
		}
	};

	/* Contact: <sip:user@example.com?Route=%3Csip:sip.example.com%3E>
	 */
	struct HFContact : public HeaderField
	{
		HFContact() : HeaderField("Contact", "m")
		{
			header_params_.append("expires");
			header_params_.append("mp");
			header_params_.append("np");
			header_params_.append("pub-gruu");
			header_params_.append("q");
			header_params_.append("rc");
			header_params_.append("reg-id");
			header_params_.append("temp-gruu");
			header_params_.append("temp-gruu-cookie");
		}

		bool is_value_valid()
		{
			if (values_.size() < 4)
				return false;

			std::string v = values_.at(0);

			if (v.at(0) != '<' || v.at(v.size()-1) != '>')
				return false;

			return true;
		}
	};

	struct HFOrganization : public HeaderField
	{
		HFOrganization() : HeaderField("Organization", true)
		{
		}
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
	};

	struct HFRetryAfter : public HeaderField
	{
		HFRetryAfter() : HeaderField("Retry-After")
		{
			header_params_.append("duration");
		}
	};

	struct HFSubject : public HeaderField
	{
		HFSubject() : HeaderField("Subject", "s")
		{
		}
	};

	struct HFSupported : public HeaderField
	{
		HFSupported() : HeaderField("Supported", "k")
		{
		}
	};

	struct HFTimestamp : public HeaderField
	{
		HFTimestamp() : HeaderField("Timestamp")
		{
		}
	};

	struct HFUserAgent : public HeaderField
	{
		HFUserAgent() : HeaderField("User-Agent")
		{
		}
	};

	struct HFAnswerMode : public HeaderField
	{
		HFAnswerMode() : HeaderField("Answer-Mode")
		{
			header_params_.append("require");
		}
	};

	struct HFPrivAnswerMode : public HeaderField
	{
		HFPrivAnswerMode() : HeaderField("Priv-Answer-Mode")
		{
			header_params_.append("require");
		}
	};

	// -------------------- Request header -----------------------------
	struct HFAccept : public HeaderField
	{
		HFAccept() : HeaderField("Accept") // type/sub-type
		{
			header_params_.append("q");
		}
	};

	struct HFAcceptContact : public HeaderField
	{
		HFAcceptContact() : HeaderField("Accept-Contact", "a")
		{
		}
	};

	struct HFAcceptEncoding : public HeaderField
	{
		HFAcceptEncoding() : HeaderField("Accept-Encoding")
		{
			header_params_.append("q");
		}
	};

	struct HFAcceptLanguage : public HeaderField
	{
		HFAcceptLanguage() : HeaderField("Accept-Language")
		{
			header_params_.append("q");
		}
	};

	struct HFAuthorization : public HeaderField
	{
		HFAuthorization() : HeaderField("Authorization")
		{
			header_params_.append("algorithm");
			header_params_.append("auts");
			header_params_.append("cnonce");
			header_params_.append("nc");
			header_params_.append("nonce");
			header_params_.append("opaque");
			header_params_.append("qop");
			header_params_.append("realm");
			header_params_.append("response");
			header_params_.append("uri");
			header_params_.append("username");
		}
	};

	struct HFCallInfo : public HeaderField
	{
		HFCallInfo() : HeaderField("Call-Info", true)
		{
			header_params_.append("m");
			header_params_.append("purpose");
		}
	};

	struct HFEvent : public HeaderField
	{
		HFEvent() : HeaderField("Event", "o")
		{
			header_params_.append("adaptive-min-rate");
			header_params_.append("body");
			header_params_.append("call-id");
			header_params_.append("effective-by");
			header_params_.append("from-tag");
			header_params_.append("id");
			header_params_.append("include-session-description");
			header_params_.append("max-rate");
			header_params_.append("min-rate");
			header_params_.append("model");
			header_params_.append("profile-type");
			header_params_.append("shared");
			header_params_.append("to-tag");
			header_params_.append("vendor");
			header_params_.append("version");
		}
	};

	struct HFInReplyTo : public HeaderField
	{
		HFInReplyTo() : HeaderField("In-Reply-To")
		{
		}
	};

	struct HFJoin : public HeaderField
	{
		HFJoin() : HeaderField("Join")
		{
		}
	};

	struct HFPriority : public HeaderField
	{
		HFPriority() : HeaderField("Priority", true)
		{
		}
	};

	struct HFPrivacy : public HeaderField
	{
		HFPrivacy() : HeaderField("Privacy", true)
		{
		}
	};

	struct HFProxyAuthorization : public HeaderField
	{
		HFProxyAuthorization() : HeaderField("Proxy-Authorization", true)
		{
			header_params_.append("algorithm");
			header_params_.append("auts");
			header_params_.append("cnonce");
			header_params_.append("nc");
			header_params_.append("nonce");
			header_params_.append("opaque");
			header_params_.append("qop");
			header_params_.append("realm");
			header_params_.append("response");
			header_params_.append("uri");
			header_params_.append("username");
		}
	};

	struct HFProxyRequire : public HeaderField
	{
		HFProxyRequire() : HeaderField("Proxy-Require", true)
		{
		}
	};

	struct HFPOSPAuthToken : public HeaderField
	{
		HFPOSPAuthToken() : HeaderField("P-OSP-Auth-Token")
		{
		}
	};

	struct HFPAssertedIdentity : public HeaderField
	{
		HFPAssertedIdentity() : HeaderField("P-Asserted-Identity")
		{
		}
	};

	struct HFPPreferredIdentity : public HeaderField
	{
		HFPPreferredIdentity() : HeaderField("P-Preferred-Identity")
		{
		}
	};

	struct HFMaxForwards : public HeaderField
	{
		HFMaxForwards() : HeaderField("Max-Forwards", true)
		{
		}
	};

	struct HFReason : public HeaderField
	{
		HFReason() : HeaderField("Reason", true)
		{
			header_params_.append("cause");
			header_params_.append("text");
		}
	};

	struct HFReferTo : public HeaderField
	{
		HFReferTo() : HeaderField("Refer-To", "r")
		{
		}
	};

	/* Referred-By: <sip:user@host.com>
	 */
	struct HFReferredBy : public HeaderField
	{
		HFReferredBy() : HeaderField("Referred-By", "b")
		{
		}
	};

	struct HFReplyTo : public HeaderField
	{
		HFReplyTo() : HeaderField("Replay-To")
		{
		}
	};

	struct HFReplaces : public HeaderField
	{
		HFReplaces() : HeaderField("Replaces")
		{
		}
	};

	struct HFRejectContact : public HeaderField
	{
		HFRejectContact() : HeaderField("Reject-Contact", "j")
		{
		}
	};

	struct HFRequestDisposition : public HeaderField
	{
		HFRequestDisposition() : HeaderField("Request-Disposition")
		{
		}
	};

	/* Require: 100rel
	 */
	struct HFRequire : public HeaderField
	{
		HFRequire() : HeaderField("Require", true)
		{
		}
	};

	struct HFRoute : public HeaderField
	{
		HFRoute() : HeaderField("Route", true)
		{
		}
	};

	struct HFRack : public HeaderField
	{
		HFRack() : HeaderField("RACK")
		{
		}
	};

	struct HFSessionExpires : public HeaderField
	{
		HFSessionExpires() : HeaderField("Session-Expires", "x")
		{
		}
	};

	struct HFSubscriptionState : public HeaderField
	{
		HFSubscriptionState() : HeaderField("Subscription-State")
		{
			header_params_.append("adaptive-min-rate");
			header_params_.append("expires");
			header_params_.append("max-rate");
			header_params_.append("min-rate");
			header_params_.append("reason");
			header_params_.append("retry-after");
		}
	};

	// -------------------- Response header -----------------------------
	struct HFAuthenticationInfo : public HeaderField
	{
		HFAuthenticationInfo() : HeaderField("Authentication-Info")
		{
			header_params_.append("cnonce");
			header_params_.append("nc");
			header_params_.append("nextnonce");
			header_params_.append("qop");
			header_params_.append("rspauth");
		}
	};

	struct HFErrorInfo : public HeaderField
	{
		HFErrorInfo() : HeaderField("Error-Info", true)
		{
		}
	};

	struct HFMinExpires : public HeaderField
	{
		HFMinExpires() : HeaderField("Min-Expires")
		{
		}
	};

	struct HFMinSE : public HeaderField
	{
		HFMinSE() : HeaderField("Min-SE")
		{
		}
	};

	struct HFProxyAuthenticate : public HeaderField
	{
		HFProxyAuthenticate() : HeaderField("Proxy-Authenticate", true)
		{
			header_params_.append("algorithm");
			header_params_.append("domain");
			header_params_.append("nonce");
			header_params_.append("opaque");
			header_params_.append("qop");
			header_params_.append("realm");
			header_params_.append("stale");
		}
	};

	struct HFServer : public HeaderField
	{
		HFServer() : HeaderField("Server")
		{
		}
	};

	/* Unsupported: 100rel
	 */
	struct HFUnsupported : public HeaderField
	{
		HFUnsupported() : HeaderField("Unsupported")
		{
		}
	};

	struct HFWarning : public HeaderField
	{
		HFWarning() : HeaderField("Warning")
		{
		}
	};

	struct HFWWWAuthenticate : public HeaderField
	{
		HFWWWAuthenticate() : HeaderField("WWW-Authenticate", true)
		{
			header_params_.append("algorithm");
			header_params_.append("domain");
			header_params_.append("nonce");
			header_params_.append("opaque");
			header_params_.append("qop");
			header_params_.append("realm");
			header_params_.append("stale");
		}
	};

	struct HFRSeq : public HeaderField
	{
		HFRSeq() : HeaderField("RSeq")
		{
		}
	};

	struct HFAllow : public HeaderField
	{
		HFAllow() : HeaderField("Allow")
		{
		}
	};

	struct HFContentEncoding : public HeaderField
	{
		HFContentEncoding() : HeaderField("Content-Encoding", "e")
		{
		}
	};

	struct HFContentLength : public HeaderField
	{
		HFContentLength() : HeaderField("Content-Length", "l", true)
		{
		}
	};

	struct HFContentLanguage : public HeaderField
	{
		HFContentLanguage() : HeaderField("Content-Language")
		{
		}
	};

	struct HFContentType : public HeaderField
	{
		HFContentType() : HeaderField("Content-Type", "c")
		{
		}
	};

	struct HFExpires : public HeaderField
	{
		HFExpires() : HeaderField("Expires")
		{
		}
	};

	struct HFMIMEVersion : public HeaderField
	{
		HFMIMEVersion() : HeaderField("MIME-Version")
		{
		}
	};

	struct RequestLine
	{
		MethodMap method_;
		std::string request_uri_;
		std::string version_;

		RequestLine()
		{
			version_ = SIP_VERSION_2_0;
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
	};

	struct ResponseStatus
	{
		std::string version_;
		RespCode resp_code_; // status_code_, reason_parase_

		ResponseStatus()
		{
			version_ = SIP_VERSION_2_0;
			resp_code_ = SIP_RESPONSE_SUCCESSFUL;
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
	};

	struct HeaderFields
	{
		RequestLine req_line_;
		ResponseStatus resp_status_;
		// mandatory
		HeaderFieldList<HFCallId> call_id_;
		HeaderFieldList<HFCSeq> cseq_;
		HeaderFieldList<HFFrom> from_;
		HeaderFieldList<HFTo> to_;
		HeaderFieldList<HFVia> via_;
		// Optional
		HeaderFieldList<HFAlertInfo> alert_info_;
		HeaderFieldList<HFAllowEvents> allow_events_;
		HeaderFieldList<HFDate> date_;
		HeaderFieldList<HFContact> contact_;
		HeaderFieldList<HFOrganization> organization_;
		HeaderFieldList<HFRecordRoute> record_route_;
		HeaderFieldList<HFRetryAfter> retry_after_; // in second
		HeaderFieldList<HFSubject> subject_;
		HeaderFieldList<HFSupported> supported_;
		HeaderFieldList<HFTimestamp> timestamp_;
		HeaderFieldList<HFUserAgent> user_agent_;
		HeaderFieldList<HFAnswerMode> answer_mode_;
		HeaderFieldList<HFPrivAnswerMode> priv_answer_mode_;
		// request header fields
		HeaderFieldList<HFAccept> accept_; // type/sub-type
		HeaderFieldList<HFAcceptContact> accept_contact_;
		HeaderFieldList<HFAcceptEncoding> accept_encoding_;
		HeaderFieldList<HFAcceptLanguage> accept_language_;
		HeaderFieldList<HFAuthorization> authorization_;
		HeaderFieldList<HFCallInfo> call_info_;
		HeaderFieldList<HFEvent> event_;
		HeaderFieldList<HFInReplyTo> in_replay_to_;
		HeaderFieldList<HFJoin> join_;
		HeaderFieldList<HFPriority> priority_;
		HeaderFieldList<HFPrivacy> privacy_;
		HeaderFieldList<HFProxyAuthorization> proxy_authorization_;
		HeaderFieldList<HFProxyRequire> proxy_require_;
		HeaderFieldList<HFPOSPAuthToken> p_osp_auth_token_;
		HeaderFieldList<HFPAssertedIdentity> p_asserted_identity_;
		HeaderFieldList<HFPPreferredIdentity> p_preferred_identity_;
		HeaderFieldList<HFMaxForwards> max_forwards_;
		HeaderFieldList<HFReason> reason_;
		HeaderFieldList<HFReferTo> refer_to_;
		HeaderFieldList<HFReferredBy> referred_by_;
		HeaderFieldList<HFReplyTo> reply_to_;
		HeaderFieldList<HFReplaces> replaces_;
		HeaderFieldList<HFRejectContact> reject_contact_;
		HeaderFieldList<HFRequestDisposition> request_disposition_;
		HeaderFieldList<HFRequire> require_;
		HeaderFieldList<HFRoute> route_;
		HeaderFieldList<HFRack> rack_;
		HeaderFieldList<HFSessionExpires> session_expires_; // in second
		HeaderFieldList<HFSubscriptionState> subscription_state_;
		// response header fields
		HeaderFieldList<HFAuthenticationInfo> authentication_info_;
		HeaderFieldList<HFErrorInfo> error_info_;
		HeaderFieldList<HFMinExpires> min_expires_;
		HeaderFieldList<HFMinSE> min_se_;
		HeaderFieldList<HFProxyAuthenticate> proxy_authenticate_;
		HeaderFieldList<HFServer> server_;
		HeaderFieldList<HFUnsupported> unsupported_;
		HeaderFieldList<HFWarning> warning_;
		HeaderFieldList<HFWWWAuthenticate> www_authenticate_;
		HeaderFieldList<HFRSeq> rseq_;
		// message header fields
		HeaderFieldList<HFAllow> allow_;
		HeaderFieldList<HFContentEncoding> content_encoding_;
		HeaderFieldList<HFContentLength> content_length_;
		HeaderFieldList<HFContentLanguage> content_language_;
		HeaderFieldList<HFContentType> content_type_;
		HeaderFieldList<HFExpires> expires_; // in second
		HeaderFieldList<HFMIMEVersion> mime_version_;

		HeaderFileds()
		{
			init_allowed_fields();
		}

	protected:
		std::map<std::string, HeaderFieldList<HeaderFields&> > allowed_fields_;
		void init_allowed_fields();
	};

} // namespace EasySip


