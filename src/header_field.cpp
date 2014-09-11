/*
 * src/header_field.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "header_field.h"

namespace EasySip
{
	void RequestLine::parse(std::string &msg, size_t &pos)
	{
		size_t next = 0;
		// read method
		next = msg.find_first_of(" ", pos);
		method_.Name(msg.substr(pos, next-pos));
		pos = next + 1;
		// read request-uri
		next = msg.find_first_of(" ", pos);
		request_uri_ = msg.substr(pos, next-pos);
		pos = next + 1;
		// read version
		next = msg.find_first_of(".", pos);
		version_ = msg.substr(pos, next-pos);
		pos = next + 1;
		next = msg.find_first_of("1234567890", pos);
		version_ += msg.substr(pos, next-pos);
		pos = next + 1;
	}

	std::ostream& operator<< (std::ostream& o, HeaderField &hf)
	{
		o << hf.field_ << ": ";

		hf.generate_values();

		for (Values::iterator it = hf.values_.begin();
			it != hf.values_.end(); it++)
		{
			o << *it;
			
			if (std::distance(hf.values_.begin(), it) < (int)hf.values_.size()-1)
				o << " ";
		}
		
		o << hf.header_params_ << "\n";

		return o;
	}

	std::string HeaderField::operator() ()
	{
		std::ostringstream o;
		o << *this;

		return o.str();
	}

	HFVia::HFVia() : HeaderField("Via", "v", true)
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

	void HFVia::generate_values()
	{
		if (proto_.size())
			values_.push_back(proto_);

		if (addr_.size())
			values_.push_back(addr_);
	}

	void HFVia::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFFrom::generate_values()
	{
		if (user_name_.size())
			values_.push_back(user_name_);

		std::ostringstream o;
		o << uri_;
		values_.push_back(o.str());
	}

	void HFFrom::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFCSeq::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFCSeq::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFCallId::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFCallId::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAlertInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAlertInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAllowEvents::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAllowEvents::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFDate::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFDate::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContact::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContact::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFContact::HFContact() : HeaderField("Contact", "m")
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

//	void HFOrganization::generate_values()
//	{
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//	}

	void HFOrganization::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRecordRoute::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRecordRoute::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRetryAfter::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRetryAfter::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSubject::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSubject::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSupported::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSupported::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFTimestamp::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFTimestamp::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFUserAgent::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFUserAgent::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAnswerMode::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAnswerMode::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPrivAnswerMode::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPrivAnswerMode::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HeaderFields::init_allowed_fields()
	{
		allowed_fields_.insert("CallId");
		allowed_fields_.insert("CSeq");
		allowed_fields_.insert("From");
		allowed_fields_.insert("To");
		allowed_fields_.insert("Via");
		allowed_fields_.insert("Alert-Info");
		allowed_fields_.insert("Allow-Events");
		allowed_fields_.insert("Date");
		allowed_fields_.insert("Contact");
		allowed_fields_.insert("Organization");
		allowed_fields_.insert("Record-Route");
		allowed_fields_.insert("Retry-After");
		allowed_fields_.insert("Subject");
		allowed_fields_.insert("Supported");
		allowed_fields_.insert("Timestamp");
		allowed_fields_.insert("User-Agent");
		allowed_fields_.insert("Answer-Mode");
		allowed_fields_.insert("Priv-Answer-Mode");
		allowed_fields_.insert("Accept");
		allowed_fields_.insert("Accept-Contact");
		allowed_fields_.insert("Accept-Encoding");
		allowed_fields_.insert("Accept-Language");
		allowed_fields_.insert("Authorization");
		allowed_fields_.insert("Call-Info");
		allowed_fields_.insert("Event");
		allowed_fields_.insert("In-Reply-To");
		allowed_fields_.insert("Join");
		allowed_fields_.insert("Priority");
		allowed_fields_.insert("Privacy");
		allowed_fields_.insert("Proxy-Authorization");
		allowed_fields_.insert("Proxy-Require");
		allowed_fields_.insert("P-OSP-AuthToken");
		allowed_fields_.insert("PAsserted-Identity");
		allowed_fields_.insert("PPreferred-Identity");
		allowed_fields_.insert("Max-Forwards");
		allowed_fields_.insert("Reason");
		allowed_fields_.insert("Refer-To");
		allowed_fields_.insert("Referred-By");
		allowed_fields_.insert("Reply-To");
		allowed_fields_.insert("Replaces");
		allowed_fields_.insert("Reject-Contact");
		allowed_fields_.insert("Request-Disposition");
		allowed_fields_.insert("Require");
		allowed_fields_.insert("Route");
		allowed_fields_.insert("Rack");
		allowed_fields_.insert("Session-Expires");
		allowed_fields_.insert("Subscription-State");
		allowed_fields_.insert("AuthenticationInfo");
		allowed_fields_.insert("Error-Info");
		allowed_fields_.insert("Min-Expires");
		allowed_fields_.insert("Min-SE");
		allowed_fields_.insert("Proxy-Authenticate");
		allowed_fields_.insert("Server");
		allowed_fields_.insert("Unsupported");
		allowed_fields_.insert("Warning");
		allowed_fields_.insert("WWW-Authenticate");
		allowed_fields_.insert("RSeq");
		allowed_fields_.insert("Allow");
		allowed_fields_.insert("Content-Encoding");
		allowed_fields_.insert("Content-Length");
		allowed_fields_.insert("Content-Language");
		allowed_fields_.insert("Content-Type");
		allowed_fields_.insert("Expires");
		allowed_fields_.insert("MIME-Version");
	}

	HeaderFields::HeaderFields()
	{
		init_allowed_fields();
	}

	HeaderFields::~HeaderFields()
	{
	}

} // namespace EasySip
