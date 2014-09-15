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
						header_params_.set_value_by_name(name, value);
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
						header_params_.set_value_by_name(name, value);
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
						header_params_.set_value_by_name(name, value);
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
				case '\n':
				case '\r':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.set_value_by_name(name, value);
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
				case '\n':
				case '\r':
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
				case '\n':
				case '\r':
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
						header_params_.set_value_by_name(name, value);
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
				case '\n':
				case '\r':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.set_value_by_name(name, value);
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

	void HFProxyRequire::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFProxyRequire::parse(std::string &msg, size_t &pos)
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

	void HFMaxForwards::generate_values()
	{
		values_ = max_fw_;
	}

	void HFMaxForwards::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_DIGIT
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\n':
				case '\r':
				{
					if (max_fw_.empty())
						max_fw_ = buffer;	

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

	void HFRequire::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFRequire::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
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

	void HFMinExpires::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFMinExpires::parse(std::string &msg, size_t &pos)
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
		o << code_ << ' ' << agent_ << ' ' << text_;
		values_ = o.str();
	}

	void HFWarning::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_dquote = false;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_ALPHA_NUM
				case '-':
				{
					buffer += msg.at(pos++);
					break;
				}
				case ' ':
				{
					if (code_.empty())
						code_ = buffer;
					pos++;
					buffer.clear();
					break;
				}
				case '"':
				{
					in_dquote = !in_dquote;

					if (!in_dquote)
					{
						buffer += msg.at(pos);
						if (text_.empty())
							text_ = buffer;
					}

					pos++;
					buffer.clear();
					break;
				}
				case '\n':
				case '\r':
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

	void HFContentLength::generate_values()
	{
		values_ = length_;
	}

	void HFContentLength::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			if (pos+1 >= msg.size()) break;
			switch(msg.at(pos))
			{
				CASE_DIGIT
				{
					buffer += msg.at(pos++);
					break;
				}
				case '\n':
				case '\r':
				{
					if (length_.empty())
						length_ = buffer;

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
				case '\n':
				case '\r':
				{
					if (read_head_param)
					{
						value = buffer;
						std::cout << name << ':' << value << '\n';
						header_params_.set_value_by_name(name, value);
						name.clear();
						value.clear();
						read_head_param = false;
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
						header_params_.set_value_by_name(name, value);
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

	void HFExpires::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFExpires::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFMIMEVersion::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HFMIMEVersion::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	void HeaderFields::init_allowed_fields()
	{
//		 allowed_fields_["CallId"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&              call_id_);
//		 allowed_fields_["CSeq"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                cseq_);
//		 allowed_fields_["From"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                from_);
//		 allowed_fields_["To"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                  to_);
//		 allowed_fields_["Via"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                 via_);
//		 allowed_fields_["Alert-Info"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&          alert_info_);
//		 allowed_fields_["Allow-Events"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        allow_events_);
//		 allowed_fields_["Date"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                date_);
//		 allowed_fields_["Contact"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             contact_);
//		 allowed_fields_["Organization"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        organization_);
//		 allowed_fields_["Record-Route"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        record_route_);
//		 allowed_fields_["Retry-After"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         retry_after_);
//		 allowed_fields_["Subject"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             subject_);
//		 allowed_fields_["Supported"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&           supported_);
//		 allowed_fields_["Timestamp"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&           timestamp_);
//		 allowed_fields_["User-Agent"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&          user_agent_);
//		 allowed_fields_["Answer-Mode"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         answer_mode_);
//		 allowed_fields_["Priv-Answer-Mode"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&    priv_answer_mode_);
//		 allowed_fields_["Accept"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&              accept_);
//		 allowed_fields_["Accept-Contact"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&      accept_contact_);
//		 allowed_fields_["Accept-Encoding"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&     accept_encoding_);
//		 allowed_fields_["Accept-Language"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&     accept_language_);
//		 allowed_fields_["Authorization"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&       authorization_);
//		 allowed_fields_["Call-Info"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&           call_info_);
//		 allowed_fields_["Event"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&               event_);
//		 allowed_fields_["In-Reply-To"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         in_replay_to_);
//		 allowed_fields_["Join"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                join_);
//		 allowed_fields_["Priority"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&            priority_);
//		 allowed_fields_["Privacy"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             privacy_);
//		 allowed_fields_["Proxy-Authorization"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(& proxy_authorization_);
//		 allowed_fields_["Proxy-Require"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&       proxy_require_);
//		 allowed_fields_["P-OSP-AuthToken"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&     p_osp_auth_token_);
//		 allowed_fields_["PAsserted-Identity"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&  p_asserted_identity_);
//		 allowed_fields_["PPreferred-Identity"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(& p_preferred_identity_);
//		 allowed_fields_["Max-Forwards"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        max_forwards_);
//		 allowed_fields_["Reason"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&              reason_);
//		 allowed_fields_["Refer-To"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&            refer_to_);
//		 allowed_fields_["Referred-By"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         referred_by_);
//		 allowed_fields_["Reply-To"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&            reply_to_);
//		 allowed_fields_["Replaces"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&            replaces_);
//		 allowed_fields_["Reject-Contact"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&      reject_contact_);
//		 allowed_fields_["Request-Disposition"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(& request_disposition_);
//		 allowed_fields_["Require"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             require_);
//		 allowed_fields_["Route"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&               route_);
//		 allowed_fields_["Rack"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                rack_);
//		 allowed_fields_["Session-Expires"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&     session_expires_);
//		 allowed_fields_["Subscription-State"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&  subscription_state_);
//		 allowed_fields_["AuthenticationInfo"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&  authentication_info_);
//		 allowed_fields_["Error-Info"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&          error_info_);
//		 allowed_fields_["Min-Expires"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         min_expires_);
//		 allowed_fields_["Min-SE"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&              min_se_);
//		 allowed_fields_["Proxy-Authenticate"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&  proxy_authenticate_);
//		 allowed_fields_["Server"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&              server_);
//		 allowed_fields_["Unsupported"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&         unsupported_);
//		 allowed_fields_["Warning"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             warning_);
//		 allowed_fields_["WWW-Authenticate"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&    www_authenticate_);
//		 allowed_fields_["RSeq"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&                rseq_);
//		 allowed_fields_["Allow"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&               allow_);
//		 allowed_fields_["Content-Encoding"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&    content_encoding_);
//		 allowed_fields_["Content-Length"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&      content_length_);
//		 allowed_fields_["Content-Language"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&    content_language_);
//		 allowed_fields_["Content-Type"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        content_type_);
//		 allowed_fields_["Expires"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&             expires_);
//		 allowed_fields_["MIME-Version"] = reinterpret_cast<HeaderFieldList<HeaderField>* >(&        mime_version_);

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
