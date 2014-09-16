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
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			method_.Name(msg.substr(pos, next-pos));
			pos = next + 1;
		}
		// read request-uri
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			request_uri_ = msg.substr(pos, next-pos);
			pos = next + 1;
		}

		// read version
		if ((next = msg.find_first_of("\n", pos)) != std::string::npos)
		{
			version_ = msg.substr(pos, next-pos);
			pos = next + 1;
		}
	}

	void ResponseStatus::parse(std::string &msg, size_t &pos)
	{
		size_t next = 0;
		// read version
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			version_ = msg.substr(pos, next-pos);
			pos = next + 1;
		}
		// read code
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			int code;
			std::istringstream in(msg.substr(pos, next-pos));
			in >> code;
			resp_code_.Code(code);
			pos = next + 1;
		}
		// read reason
		if ((next = msg.find_first_of("\n", pos)) != std::string::npos)
		{
			resp_code_.Name(msg.substr(pos, next-pos));
			pos = next + 1;
		}
	}

	std::ostream& operator<< (std::ostream& o, HeaderField &hf)
	{
		o << hf.field_ << ": ";
		hf.generate_values();

		o << hf.Values();
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
		values_ = sent_proto_ + ' ' + sent_by_;
	}

	void HFVia::parse(std::string &msg, size_t &pos)
	{
		bool read_head_param = false, run = true;
		std::string buffer, name, value;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_ALPHA_NUM
				case ':':
				case '-':
				case '.':
				case '/':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\t':
				{
					pos++;
					break;
				}
				case ' ':
				{
					if (sent_proto_.empty())
					{
						sent_proto_ = buffer;
					}
					else if (sent_by_.empty())
					{
						sent_by_ = buffer;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (sent_by_.empty())
					{
						sent_by_ = buffer;
					}

					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}
					else
					{
						read_head_param = true;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					name = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (sent_by_.empty())
					{
						sent_by_ = buffer;
					}

					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}

					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false;read_head_param = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "' :" << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFBase_1_::generate_values()
	{
		std::ostringstream o;

		o << name_ << ' ' << uri_;
		values_ = o.str();
	}

	void HFBase_1_::parse(std::string &msg, size_t &pos)
	{
		size_t sp_nr = 0;
		bool read_head_param = false, run = true, read_uri = false, in_dquote = false, read_uri_param = false;
		std::string buffer, name, value;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				case '"':
				{
					in_dquote = !in_dquote;

					if (!in_dquote)
					{
						buffer += msg.at(pos);

						if (name_.empty())
							name_ = buffer;

						pos++;
						buffer.clear();
						break;
					}
				}
				CASE_ALPHA_NUM
				case '-':
				case '_':
				case '.':
				case '/':
				case ':':
				case '@':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\t':
				{
					pos++;
					break;
				}
				case ' ':
				{
					if ('.' == msg.at(pos-1))
					{
						buffer += msg.at(pos++);
						break;
					}

					if ('>' == msg.at(pos-1))
					{
						pos++;
						buffer.clear();
						break;
					}

					sp_nr++;

					if (name_.empty())
					{
						name_ = buffer;
					}
					else if (uri_.uri_.empty())
					{
						uri_.uri_ = buffer;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '<':
				{
					read_uri = true;
					pos++;
					buffer.clear();
					break;
				}
				case '>':
				{
					read_uri = false;
					read_uri_param = false;
					uri_.uri_ = buffer;
					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (uri_.uri_.empty())
					{
						uri_.uri_ = buffer;
					}

					if (read_uri)
					{
						if (read_uri_param)
						{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						uri_.set_param(name, value);
						name.clear();
						value.clear();
						}
						else
						{
							read_uri_param = true;
						}
					}
					else
					{
						if (read_head_param)
						{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
						}
						else
						{
							read_head_param = true;
						}
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					name = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}

					if (uri_.uri_.empty())
					{
						uri_.uri_ = buffer;
					}

					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false;read_head_param = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "' :" << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFCSeq::generate_values()
	{
		values_ = cseq_ + ' ' + method_;
	}

	void HFCSeq::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;
		size_t sp_nr = 0;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_ALPHA_NUM
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\t':
				{
					pos++;
					break;
				}
				case ' ':
				{
					sp_nr++;
	
					if (1 == sp_nr)
					{
						cseq_ = buffer;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (method_.empty())
						method_ = buffer;
	
					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "' : " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFCallId::generate_values()
	{
		values_ = id_;
	}

	void HFCallId::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_WORD
				case '@':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (id_.empty())
						id_ = buffer;

					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "' : " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
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
		std::ostringstream o;
		o << uri_;
		values_ = o.str();
	}

	void HFContact::parse(std::string &msg, size_t &pos)
	{
		bool read_head_param = false, run = true, read_uri = false, read_uri_param = false;
		std::string buffer, name, value;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_ALPHA_NUM
				case '*':
				case '-':
				case '.':
				case '/':
				case ':':
				case '@':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\t':
				{
					pos++;
					break;
				}
				case '<':
				{
					read_uri = true;
					pos++;
					buffer.clear();
					break;
				}
				case '>':
				{
					read_uri = false;

					if (read_uri_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						uri_.set_param(name, value);
						name.clear();
						value.clear();
						read_uri_param = false;
					}
					else
					{
						uri_.uri_ = buffer;
					}

					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (uri_.uri_.empty())
					{
						uri_.uri_ = buffer;
					}

					if (read_uri)
					{
						if (read_uri_param)
						{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						uri_.set_param(name, value);
						name.clear();
						value.clear();
						}
						else
						{
							read_uri_param = true;
						}
					}
					else
					{
						if (read_head_param)
						{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
						}
						else
						{
							read_head_param = true;
						}
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					if (!read_uri_param)
						read_head_param = true;
					name = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}

					if (uri_.uri_.empty())
						uri_.uri_ = buffer;

					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false;read_head_param = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
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

	void HFOrganization::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

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

	void HFAccept::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAccept::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptContact::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptContact::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptEncoding::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptEncoding::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptLanguage::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAcceptLanguage::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFAuthorization::HFAuthorization() : HeaderField("Authorization")
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

	void HFAuthorization::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAuthorization::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFCallInfo::HFCallInfo() : HeaderField("Call-Info", true)
	{
		header_params_.append("m");
		header_params_.append("purpose");
	}

	void HFCallInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFCallInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFEvent::HFEvent() : HeaderField("Event", "o")
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

	void HFEvent::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFEvent::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFInReplyTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFInReplyTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFJoin::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFJoin::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPriority::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPriority::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPrivacy::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPrivacy::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFProxyAuthorization::HFProxyAuthorization() : HeaderField("Proxy-Authorization", true)
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

	void HFProxyAuthorization::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFProxyAuthorization::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPOSPAuthToken::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPOSPAuthToken::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPAssertedIdentity::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPAssertedIdentity::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPPreferredIdentity::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFPPreferredIdentity::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReason::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReason::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReferTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReferTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReferredBy::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReferredBy::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReplyTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReplyTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReplaces::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFReplaces::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRejectContact::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRejectContact::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRequestDisposition::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRequestDisposition::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFBase_3_::generate_values()
	{
		values_.clear();

		for (auto &it : options_)
		{
			values_ += it + ' ';
		}

		values_.erase(values_.size()-1);
	}

	void HFBase_3_::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_TOKEN
				{
					buffer += msg.at(pos++);
					break;
				}
				case ',':
				{
					if (buffer.size())
					{
						options_.insert(buffer);
					}
				}
				case ' ':
				case '\t':
				{
					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (buffer.size())
						options_.insert(buffer);

					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false)
				
					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFRoute::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRoute::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRack::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRack::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSessionExpires::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSessionExpires::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFSubscriptionState::HFSubscriptionState() : HeaderField("Subscription-State")
	{
		header_params_.append("adaptive-min-rate");
		header_params_.append("expires");
		header_params_.append("max-rate");
		header_params_.append("min-rate");
		header_params_.append("reason");
		header_params_.append("retry-after");
	}

	void HFSubscriptionState::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFSubscriptionState::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFAuthenticationInfo::HFAuthenticationInfo() : HeaderField("Authentication-Info")
	{
		header_params_.append("cnonce");
		header_params_.append("nc");
		header_params_.append("nextnonce");
		header_params_.append("qop");
		header_params_.append("rspauth");
	}

	void HFAuthenticationInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAuthenticationInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFErrorInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFErrorInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFMinSE::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFMinSE::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	HFProxyAuthenticate::HFProxyAuthenticate() : HeaderField("Proxy-Authenticate", true)
	{
		header_params_.append("algorithm");
		header_params_.append("domain");
		header_params_.append("nonce");
		header_params_.append("opaque");
		header_params_.append("qop");
		header_params_.append("realm");
		header_params_.append("stale");
	}

	void HFProxyAuthenticate::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFProxyAuthenticate::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFServer::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFServer::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFUnsupported::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFUnsupported::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFWarning::generate_values()
	{
		std::ostringstream o;

		for (auto &it : warn_values_)
		{
			o << it << ',';
		}

		values_ = o.str();

		if (values_.size() && values_.at(values_.size()-1) == ',')
		{
			values_.erase(values_.size()-1);
		}
	}

	void HFWarning::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_dquote = false;
		std::string buffer;
		size_t index = 0;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_TOKEN
				case '(':
				case ')':
				case ']':
				case '[':
				case '<':
				case '>':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\t':
				{
					pos++;
					buffer.clear();
					break;
				}
				case ' ':
				{
					if (in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					if (warn_values_.at(index).code_.empty())
						warn_values_.at(index).code_ = buffer;
				
					pos++;
					buffer.clear();
					break;
				}
				case ',':
				{
					if (in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					index++;
					warn_values_.resize(warn_values_.size()+1);
					pos++;
					buffer.clear();
					break;
				}
				case '"':
				{
					in_dquote = !in_dquote;

					if (!in_dquote)
					{
						if (warn_values_.at(index).text_.empty())
							warn_values_.at(index).text_ = buffer;
					}

					pos++;
					buffer.clear();
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	HFWWWAuthenticate::HFWWWAuthenticate() : HeaderField("WWW-Authenticate", true)
	{
		header_params_.append("algorithm");
		header_params_.append("domain");
		header_params_.append("nonce");
		header_params_.append("opaque");
		header_params_.append("qop");
		header_params_.append("realm");
		header_params_.append("stale");
	}

	void HFWWWAuthenticate::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFWWWAuthenticate::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRSeq::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRSeq::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAllow::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFAllow::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContentEncoding::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContentEncoding::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContentLanguage::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContentLanguage::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFContentType::generate_values()
	{
		std::ostringstream o;
		o << discrete_ty_ << '/' << composite_ty_;
		values_ = o.str();
	}

	void HFContentType::parse(std::string &msg, size_t &pos)
	{
		bool run = true, read_head_param = false;
		std::string buffer, name, value;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_LOWER_ALPHA
				CASE_DIGIT
				case '-':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '/':
				{
					pos++;
					discrete_ty_ = buffer;
					buffer.clear();
					break;
				}
				case ' ':
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}

					if (composite_ty_.empty())
					{
						composite_ty_ = buffer;
					}

					
					if (pos+1 >= msg.size())
					{
						run = false;
						break;
					}

					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					name = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (composite_ty_.empty())
					{
						composite_ty_ = buffer;
					}

					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.append(name, value);//.set_value_by_name(name, value);
						name.clear();
						value.clear();
					}
					else
					{
						read_head_param = true;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFBase_2_::generate_values()
	{
		values_ = digit_value_;
	}

	void HFBase_2_::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size())
			{
				if (digit_value_.empty())
					digit_value_ = buffer;
				break;
			}
			switch(msg.at(pos))
			{
				CASE_DIGIT
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (digit_value_.empty())
						digit_value_ = buffer;

					run = false;

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HFMIMEVersion::generate_values()
	{
		values_ = dotted_value_;
	}

	void HFMIMEVersion::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size())
			{
				if (dotted_value_.empty())
					dotted_value_ = buffer;
				break;
			}
			switch(msg.at(pos))
			{
				CASE_DIGIT
				case '.':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (dotted_value_.empty())
						dotted_value_ = buffer;

					run = false;

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos++) << "': " << buffer << "\n";
					buffer.clear();
				}
			}
		}

		std::cout << *this;
	}

	void HeaderFields::init_allowed_fields()
	{
		allowed_fields_.push_back("CallId");
		allowed_fields_.push_back("CSeq");
		allowed_fields_.push_back("From");
		allowed_fields_.push_back("To");
		allowed_fields_.push_back("Via");
		allowed_fields_.push_back("Alert-Info");
		allowed_fields_.push_back("Allow-Events");
		allowed_fields_.push_back("Date");
		allowed_fields_.push_back("Contact");
		allowed_fields_.push_back("Organization");
		allowed_fields_.push_back("Record-Route");
		allowed_fields_.push_back("Retry-After");
		allowed_fields_.push_back("Subject");
		allowed_fields_.push_back("Supported");
		allowed_fields_.push_back("Timestamp");
		allowed_fields_.push_back("User-Agent");
		allowed_fields_.push_back("Answer-Mode");
		allowed_fields_.push_back("Priv-Answer-Mode");
		allowed_fields_.push_back("Accept");
		allowed_fields_.push_back("Accept-Contact");
		allowed_fields_.push_back("Accept-Encoding");
		allowed_fields_.push_back("Accept-Language");
		allowed_fields_.push_back("Authorization");
		allowed_fields_.push_back("Call-Info");
		allowed_fields_.push_back("Event");
		allowed_fields_.push_back("In-Reply-To");
		allowed_fields_.push_back("Join");
		allowed_fields_.push_back("Priority");
		allowed_fields_.push_back("Privacy");
		allowed_fields_.push_back("Proxy-Authorization");
		allowed_fields_.push_back("Proxy-Require");
		allowed_fields_.push_back("P-OSP-AuthToken");
		allowed_fields_.push_back("PAsserted-Identity");
		allowed_fields_.push_back("PPreferred-Identity");
		allowed_fields_.push_back("Max-Forwards");
		allowed_fields_.push_back("Reason");
		allowed_fields_.push_back("Refer-To");
		allowed_fields_.push_back("Referred-By");
		allowed_fields_.push_back("Reply-To");
		allowed_fields_.push_back("Replaces");
		allowed_fields_.push_back("Reject-Contact");
		allowed_fields_.push_back("Request-Disposition");
		allowed_fields_.push_back("Require");
		allowed_fields_.push_back("Route");
		allowed_fields_.push_back("Rack");
		allowed_fields_.push_back("Session-Expires");
		allowed_fields_.push_back("Subscription-State");
		allowed_fields_.push_back("AuthenticationInfo");
		allowed_fields_.push_back("Error-Info");
		allowed_fields_.push_back("Min-Expires");
		allowed_fields_.push_back("Min-SE");
		allowed_fields_.push_back("Proxy-Authenticate");
		allowed_fields_.push_back("Server");
		allowed_fields_.push_back("Unsupported");
		allowed_fields_.push_back("Warning");
		allowed_fields_.push_back("WWW-Authenticate");
		allowed_fields_.push_back("RSeq");
		allowed_fields_.push_back("Allow");
		allowed_fields_.push_back("Content-Encoding");
		allowed_fields_.push_back("Content-Length");
		allowed_fields_.push_back("Content-Language");
		allowed_fields_.push_back("Content-Type");
		allowed_fields_.push_back("Expires");
		allowed_fields_.push_back("MIME-Version");
	}

	HeaderFields::HeaderFields()
	{
		init_allowed_fields();
	}

	HeaderFields::~HeaderFields()
	{
	}

} // namespace EasySip
