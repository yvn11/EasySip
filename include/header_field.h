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

	#define return_false_if_true(c) \
	{								\
		if ((c)) return false;	\
	}

	#define ONE_HOUR 60*60 // in second

	enum
	{
		HF_CALLID = 1,
		HF_CSEQ,
		HF_FROM,
		HF_TO,
		HF_VIA,
		HF_ALERT_INFO,
		HF_ALLOW_EVENTS,
		HF_DATE,
		HF_CONTACT,
		HF_ORGANIZATION,
		HF_RECORD_ROUTE,
		HF_RETRY_AFTER,
		HF_SUBJECT,
		HF_SUPPORTED,
		HF_TIMESTAMP,
		HF_USER_AGENT,
		HF_ANSWER_MODE,
		HF_PRIV_ANSWER_MODE,
		HF_ACCEPT,
		HF_ACCEPT_CONTACT,
		HF_ACCEPT_ENCODING,
		HF_ACCEPT_LANGUAGE,
		HF_AUTHORIZATION,
		HF_CALL_INFO,
		HF_EVENT,
		HF_IN_REPLY_TO,
		HF_JOIN,
		HF_PRIORITY,
		HF_PRIVACY,
		HF_PROXY_AUTHORIZATION,
		HF_PROXY_REQUIRE,
		HF_P_OSP_AUTHTOKEN,
		HF_PASSERTED_IDENTITY,
		HF_PPREFERRED_IDENTITY,
		HF_MAX_FORWARDS,
		HF_REASON,
		HF_REFER_TO,
		HF_REFERRED_BY,
		HF_REPLY_TO,
		HF_REPLACES,
		HF_REJECT_CONTACT,
		HF_REQUEST_DISPOSITION,
		HF_REQUIRE,
		HF_ROUTE,
		HF_RACK,
		HF_SESSION_EXPIRES,
		HF_SUBSCRIPTION_STATE,
		HF_AUTHENTICATIONINFO,
		HF_ERROR_INFO,
		HF_MIN_EXPIRES,
		HF_MIN_SE,
		HF_PROXY_AUTHENTICATE,
		HF_SERVER,
		HF_UNSUPPORTED,
		HF_WARNING,
		HF_WWW_AUTHENTICATE,
		HF_RSEQ,
		HF_ALLOW,
		HF_CONTENT_ENCODING,
		HF_CONTENT_LENGTH,
		HF_CONTENT_LANGUAGE,
		HF_CONTENT_TYPE,
		HF_EXPIRES,
		HF_MIME_VERSION,
	};	

	struct HeaderField
	{
		std::string field_;
		std::string compact_form_;
		std::string values_;
		Parameters header_params_;
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

		virtual void generate_values() = 0;

		virtual void parse(std::string &msg, size_t &pos) = 0;

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

		void remove_tail_symbol(char sym)
		{
			if (values_.size() && values_.at(values_.size()-1) == sym)
				values_.erase(values_.size()-1);
		}
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

		bool operator== (HFCallId& val)
		{
			return (id_ == val.id_);
		}

		HFCallId& add_id(std::string val)
		{
			id_ = val;
			return *this;
		}
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

		HFCSeq& add_seq(std::string seq)
		{
			cseq_ = seq;
			return *this;
		}

		HFCSeq& add_method(std::string val)
		{
			method_ = val;
			return *this;
		}

		void inc_seq()
		{
			unsigned int seq;

			std::istringstream i(cseq_);
			i >> seq;
			seq++;

			std::ostringstream o;
			o << seq;
			cseq_ = o.str();
		}
	};
	
	struct HFBase_1_ : public HeaderField
	{
		ContactList cons_;

		HFBase_1_(std::string f, bool is_hbh = false) : HeaderField(f, is_hbh)
		{
//			header_params_.append("tag");
		}

		HFBase_1_(std::string f, std::string c, bool is_hbh = false) : HeaderField(f, c, is_hbh)
		{
//			header_params_.append("tag");
		}

		virtual void generate_values();
		virtual void parse(std::string &msg, size_t &pos);

		HFBase_1_& add_param(std::string key, std::string value = "")
		{
			if (!cons_.empty() && key.size())
				cons_.last()->add_param(key, value);

			return *this;
		}

		HFBase_1_& add_uri(std::string uri)
		{
			if (cons_.empty() || cons_.last()->full() || !cons_.last()->uri().empty())
			{
				cons_.append_item();
			}

			if (cons_.last()->uri().empty())
			{
				cons_.last()->uri(uri);
			}

			return *this;
		}

		HFBase_1_& add_name(std::string name)
		{
			if (cons_.empty() || cons_.last()->full())
			{
				cons_.append_item();
			}

			if (cons_.last()->name().empty())
			{
				cons_.last()->name(name);
			}

			return *this;
		}
	};

	struct HFBase_2_ : public HeaderField
	{
		std::string digit_value_;

		HFBase_2_(std::string f, bool is_hbh = false) : HeaderField(f, is_hbh)
		{
		}

		HFBase_2_(std::string f, std::string c, bool is_hbh = false) : HeaderField(f, c, is_hbh)
		{
		}

		virtual void generate_values();
		virtual void parse(std::string &msg, size_t &pos);

		virtual HFBase_2_& add_value(std::string val)
		{
			digit_value_ = val;
			return *this;
		}
	};

	struct HFBase_3_ : public HeaderField
	{
		std::vector<std::string> opts_;
		char sym_;

		HFBase_3_(std::string f, bool is_hbh = false) : HeaderField(f, is_hbh)
		{
			sym_ = ',';
		}

		HFBase_3_(std::string f, std::string c, bool is_hbh = false) : HeaderField(f, c, is_hbh)
		{
			sym_ = ',';
		}

		virtual void generate_values();
		virtual void parse(std::string &msg, size_t &pos);

		virtual HFBase_3_& add_value(std::string val)
		{
			opts_.push_back(val);
			return *this;
		}
	};
	/* From: Alice <sip:alice@atlanta.com>;tag=87263237
	 */
	struct HFFrom : public HFBase_1_
	{
		HFFrom() : HFBase_1_("From", "f")
		{
		}

		std::string name()
		{
			if (cons_.empty())
				return std::string();
			return cons_.at(0)->name();
		}

		std::string uri()
		{
			if (cons_.empty())
				return std::string();
			return cons_.at(0)->uri();
		}

		std::string tag()
		{
			return header_params_.get_value_by_name("tag");
		}
	};

	/* To: Alice <sip:alice@atlanta.com>;tag=39u292sd7
	 */
	struct HFTo : public HFBase_1_
	{
		HFTo() : HFBase_1_("To", "t")
		{
		}

		std::string name()
		{
			if (cons_.empty())
				return std::string();
			return cons_.at(0)->name();
		}

		std::string uri()
		{
			if (cons_.empty())
				return std::string();
			return cons_.at(0)->uri();
		}

		std::string tag()
		{
			return header_params_.get_value_by_name("tag");
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

		void generate_values();
		void parse(std::string &msg, size_t &pos);

		HFVia& add_proto(std::string proto)
		{
			sent_proto_ = proto;
			return *this;
		}

		HFVia& add_sentby(std::string by)
		{
			sent_by_ = by;
			return *this;
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
//			header_params_.append("appearance");
//			header_params_.append("purpose");
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
	struct HFContact : public HFBase_1_
	{
		HFContact();

		ContactList& cons()
		{
			return cons_;
		}
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
	struct HFRecordRoute : public HFBase_1_
	{
		HFRecordRoute() : HFBase_1_("Record-Route", true)
		{
		}
	};

	struct HFRetryAfter : public HeaderField
	{
		HFRetryAfter() : HeaderField("Retry-After")
		{
//			header_params_.append("duration");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFSubject : public HFBase_3_
	{
		HFSubject() : HFBase_3_("Subject", "s")
		{
			sym_ = ' ';
		}
	};

	struct HFSupported : public HFBase_3_
	{
		HFSupported() : HFBase_3_("Supported", "k")
		{
			sym_ = ' ';
		}
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
//			header_params_.append("require");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFPrivAnswerMode : public HeaderField
	{
		HFPrivAnswerMode() : HeaderField("Priv-Answer-Mode")
		{
//			header_params_.append("require");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

//	const char* accept_types[] =
//	{
//		"text", "image", "audio", "video", "application",
//		"message", "multipart"
//	};
	// -------------------- Request header -----------------------------
	struct HFAccept : public HeaderField
	{
		struct AcceptRange
		{
			std::string type_;
			std::string subtype_;

			AcceptRange()
			{
			}

			AcceptRange(std::string type, std::string subtype)
			: type_(type), subtype_(subtype)
			{
			}

			friend std::ostream& operator<< (std::ostream &o, AcceptRange &r)
			{
				o << r.type_ << '/' << r.subtype_;
				return o;
			}
		};

		std::vector<AcceptRange> ranges_;

		HFAccept() : HeaderField("Accept") // type/sub-type
		{
//			header_params_.append("q");
		}

		void generate_values();
		void parse(std::string &msg, size_t &pos);

		HFAccept& add_value(std::string type, std::string subtype)
		{
			ranges_.push_back(AcceptRange(type, subtype));
			return *this;
		}
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
//			header_params_.append("q");
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFAcceptLanguage : public HFBase_1_
	{
		HFAcceptLanguage() : HFBase_1_("Accept-Language")
		{
//			header_params_.append("q");
		}
//		void generate_values();
//		void parse(std::string &msg, size_t &pos);
	};

	struct HFAuthorization : public HeaderField
	{
		HFAuthorization();

		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFCallInfo : public HFBase_1_
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

	struct HFMaxForwards : public HFBase_2_
	{
		HFMaxForwards() : HFBase_2_("Max-Forwards", true)
		{
		}

		std::string max_forwards()
		{
			return digit_value_;
		}

		void max_forwards(std::string val)
		{
			digit_value_ = val;
		}
	};

	struct HFReason : public HeaderField
	{
		HFReason() : HeaderField("Reason", true)
		{
//			header_params_.append("cause");
//			header_params_.append("text");
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
	struct HFRequire : public HFBase_3_
	{
		HFRequire() : HFBase_3_("Require", true)
		{
		}
	};

	struct HFProxyRequire : public HFBase_3_
	{
		HFProxyRequire() : HFBase_3_("Proxy-Require", true)
		{
		}
	};

	struct HFRoute : public HFBase_1_
	{
		HFRoute() : HFBase_1_("Route", true)
		{
		}
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

	struct HFServer : public HFBase_3_
	{
		HFServer() : HFBase_3_("Server")
		{
			sym_ = ' ';
		}
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
		struct WarningValue
		{
			std::string code_;
			std::string agent_;
			std::string text_;

			friend std::ostream& operator<< (std::ostream &o, WarningValue &w)
			{
				o << w.code_;

				if (w.agent_.size())
					o << ' ' << w.agent_;

				if (w.text_.size())
					o << " \"" << w.text_ << '"';

				return o;
			}
		};

		std::vector<WarningValue> warn_vals_;

		HFWarning() : HeaderField("Warning")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFWWWAuthenticate : public HeaderField
	{
		std::string challenge_;
		Parameters digest_cln_;

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

	struct HFAllow : public HFBase_3_
	{
		HFAllow() : HFBase_3_("Allow")
		{
		}
	};

	struct HFContentEncoding : public HeaderField
	{
		HFContentEncoding() : HeaderField("Content-Encoding", "e")
		{
		}
		void generate_values();
		void parse(std::string &msg, size_t &pos);
	};

	struct HFContentLength : public HFBase_2_
	{
		HFContentLength() : HFBase_2_("Content-Length", "l", true)
		{
		}

		std::string length()
		{
			return digit_value_;
		}

		void length(std::string val)
		{
			digit_value_ = val;
		}

		void length(size_t val)
		{
			std::ostringstream o;
			o << val;
			digit_value_ = o.str();
		}
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


	struct HFMinExpires : public HFBase_2_
	{
		HFMinExpires() : HFBase_2_("Min-Expires")
		{
		}
	};

	struct HFExpires : public HFBase_2_
	{
		HFExpires() : HFBase_2_("Expires")
		{
		}

		std::string expire()
		{
			return digit_value_;
		}

		void expire(std::string val)
		{
			digit_value_ = val;
		}
	};

	struct HFMIMEVersion : public HeaderField
	{
		std::string dotted_value_;

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
			
			ret << method_.name() << " " << request_uri_ << " " << version_ << "\n";
			return ret.str();
		}

		friend std::ostream& operator<< (std::ostream &o, RequestLine req)
		{
			return o << req.method_.name() << " " << req.request_uri_ << " " << req.version_ << "\r\n";
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
			return o << res.version_ << " " << res.resp_code_ << "\r\n";
		}

		void parse(std::string &msg, size_t &pos);

		ResponseStatus& operator=(ResponseStatus resp)
		{
			version_ = resp.version_;
			resp_code_ = resp.resp_code_;
			return *this;
		}
	};

	#define out_if_not_null(o, it) 	\
	{								\
		if (it) o << *it;			\
	}

	#define out_if_not_empty(o, hf)	\
	{								\
		for (auto &it : hf) o << *it;	\
	}

	typedef std::map<std::string, size_t> T_HF_MAP;

	struct HeaderFields
	{
		std::shared_ptr<RequestLine> req_line_;
		std::shared_ptr<ResponseStatus> resp_status_;
		// mandatory
		PtsOf<HFCallId> call_id_;
		PtsOf<HFCSeq> cseq_;
		PtsOf<HFFrom> from_;
		PtsOf<HFTo> to_;
		PtsOf<HFVia> via_;
		// Optional
		PtsOf<HFAlertInfo> alert_info_;
		PtsOf<HFAllowEvents> allow_events_;
		PtsOf<HFDate> date_;
		PtsOf<HFContact> contact_;
		PtsOf<HFOrganization> organization_;
		PtsOf<HFRecordRoute> record_route_;
		PtsOf<HFRetryAfter> retry_after_; // in second
		PtsOf<HFSubject> subject_;
		PtsOf<HFSupported> supported_;
		PtsOf<HFTimestamp> timestamp_;
		PtsOf<HFUserAgent> user_agent_;
		PtsOf<HFAnswerMode> answer_mode_;
		PtsOf<HFPrivAnswerMode> priv_answer_mode_;
		// request header fields
		PtsOf<HFAccept> accept_; // type/sub-type
		PtsOf<HFAcceptContact> accept_contact_;
		PtsOf<HFAcceptEncoding> accept_encoding_;
		PtsOf<HFAcceptLanguage> accept_language_;
		PtsOf<HFAuthorization> authorization_;
		PtsOf<HFCallInfo> call_info_;
		PtsOf<HFEvent> event_;
		PtsOf<HFInReplyTo> in_replay_to_;
		PtsOf<HFJoin> join_;
		PtsOf<HFPriority> priority_;
		PtsOf<HFPrivacy> privacy_;
		PtsOf<HFProxyAuthorization> proxy_authorization_;
		PtsOf<HFProxyRequire> proxy_require_;
		PtsOf<HFPOSPAuthToken> p_osp_auth_token_;
		PtsOf<HFPAssertedIdentity> p_asserted_identity_;
		PtsOf<HFPPreferredIdentity> p_preferred_identity_;
		PtsOf<HFMaxForwards> max_forwards_;
		PtsOf<HFReason> reason_;
		PtsOf<HFReferTo> refer_to_;
		PtsOf<HFReferredBy> referred_by_;
		PtsOf<HFReplyTo> reply_to_;
		PtsOf<HFReplaces> replaces_;
		PtsOf<HFRejectContact> reject_contact_;
		PtsOf<HFRequestDisposition> request_disposition_;
		PtsOf<HFRequire> require_;
		PtsOf<HFRoute> route_;
		PtsOf<HFRack> rack_;
		PtsOf<HFSessionExpires> session_expires_; // in second
		PtsOf<HFSubscriptionState> subscription_state_;
		// response header fields
		PtsOf<HFAuthenticationInfo> authentication_info_;
		PtsOf<HFErrorInfo> error_info_;
		PtsOf<HFMinExpires> min_expires_;
		PtsOf<HFMinSE> min_se_;
		PtsOf<HFProxyAuthenticate> proxy_authenticate_;
		PtsOf<HFServer> server_;
		PtsOf<HFUnsupported> unsupported_;
		PtsOf<HFWarning> warning_;
		PtsOf<HFWWWAuthenticate> www_authenticate_;
		PtsOf<HFRSeq> rseq_;
		// message header fields
		PtsOf<HFAllow> allow_;
		PtsOf<HFContentEncoding> content_encoding_;
		PtsOf<HFContentLength> content_length_;
		PtsOf<HFContentLanguage> content_language_;
		PtsOf<HFContentType> content_type_;
		PtsOf<HFExpires> expires_; // in second
		PtsOf<HFMIMEVersion> mime_version_;

		HeaderFields();

		~HeaderFields();

	public:
		static T_HF_MAP allowed_fields_;
		static void init_allowed_fields();


	};

} // namespace EasySip
