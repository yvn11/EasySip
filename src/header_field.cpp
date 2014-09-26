/*
 * src/header_field.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "header_field.h"

namespace EasySip
{
	T_HF_MAP HeaderFields::allowed_fields_;

	int RequestLine::parse(std::string &msg, size_t &pos)
	{
		size_t next = 0;
		// read method
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			method_.name(msg.substr(pos, next-pos));
			pos = next + 1;
		}

		// read request-uri 
		if ((next = msg.find_first_of(" ", pos)) != std::string::npos)
		{
			request_uri_ = msg.substr(pos, next-pos);
			pos = next + 1;
		}
		// TODO: check uri scheme return code 416 on error

		// read version
		if ((next = msg.find_first_of("\n", pos)) != std::string::npos)
		{
			version_ = msg.substr(pos, next-pos);
			pos = next + 1;
		}

		return PROCEDURE_OK;
	}

	int ResponseStatus::parse(std::string &msg, size_t &pos)
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
			resp_code_.name(msg.substr(pos, next-pos));
			pos = next + 1;
		}

		return PROCEDURE_OK;
	}

	std::ostream& operator<< (std::ostream& o, HeaderField &hf)
	{
		o << hf.field_ << ": ";
		hf.generate_values();

		o << hf.Values();
		o << "\r\n";
//		o << hf.header_params_ << "\n";

		return o;
	}

	std::string HeaderField::operator() ()
	{
		std::ostringstream o;
		o << *this;

		return o.str();
	}

	int HFBase_1_::parse(std::string &msg, size_t &pos)
	{
		bool read_head_param = false, run = true, in_aquote = false, in_dquote = false;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				case '"':
				{
					in_dquote = !in_dquote;

					buffer += msg.at(pos++);

					if (!in_dquote)
					{
						add_name(buffer);
						buffer.clear();
					}
					break;
				}
				CASE_TOKEN
				case '/':
				case '?':
				case ':':
				case '@':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '<':
				{
					in_aquote = true;
					pos++;
					buffer.clear();
					break;
				}
				case '>':
				{
					in_aquote = false;

					if (key.size())
					{
						add_param(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_uri(buffer);
					}

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

					if (key.size())
					{
						add_param(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_uri(buffer);
					}

					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (in_aquote)
					{
						if (key.size())
						{
							add_param(key, buffer);
							key.clear();
						}
						else if (buffer.size())
						{
							add_uri(buffer);
						}
					}
					else
					{
						if (read_head_param)
						{
							header_params_.append(key, buffer);
							key.clear();
						}
						else if (buffer.size())
						{
							add_uri(buffer);
						}

						if (!read_head_param)
							read_head_param = true;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					key = buffer;
	
					buffer.clear();
					pos++;
					break;
				}
				case ' ':
				{
					if (in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					if (in_aquote)
					{
						pos++;
						break;
					}

					if (buffer.size())
					{
						add_name(buffer);
					}
					buffer.clear();
				}
				case '\t':
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (read_head_param)
					{
						header_params_.append(key, buffer);
						key.clear();
						read_head_param = false;
					}

					else if (buffer.size())
					{
						add_uri(buffer);
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}

		return PROCEDURE_OK;
	}

	void HFBase_2_::generate_values()
	{
		values_ = digit_value_;

		std::stringstream p;
		p << header_params_;

		values_ += p.str();
	}

	int HFBase_2_::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
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
//					if (digit_value_.empty())
						digit_value_ = buffer;

					run = false;

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}

		return PROCEDURE_OK;
	}

	void HFBase_3_::generate_values()
	{
		values_.clear();

		for (auto &it : opts_)
			values_ +=  it + sym_;

		remove_tail_symbol(sym_);

		if (header_params_.size())
		{
			std::ostringstream p;
			p << ";" << header_params_;
			values_ += p.str();
		}
	}

	int HFBase_3_::parse(std::string &msg, size_t &pos)
	{
		bool run = true, read_head_param = false;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				case ':':
				case '/': 
				case '@': 
				CASE_TOKEN
				case '\t':
				case ' ':
				case ',':
				{
					if (sym_ != msg.at(pos))
					{
						buffer += msg.at(pos++);
						break;
					}

					if (buffer.size())
					{
						add_value(buffer);
					}

					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					key = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (read_head_param)
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else
					{
						if (buffer.size())
							add_value(buffer);
						read_head_param = true;
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
					if (read_head_param)
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_value(buffer);
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}

		return PROCEDURE_OK;
	}

	void HFBase_4_::generate_values()
	{
		char sym = ',';
		std::ostringstream o;

		for (auto &it : its_)
		{
			o << *it << sym;
		}

		values_ = o.str();
		remove_tail_symbol(sym);

		if (header_params_.size())
		{
			std::ostringstream p;
			p << ";" << header_params_;
			values_ += p.str();
		}
	}

	int HFBase_4_::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_dquote = false;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				case '"':
				{
					in_dquote = !in_dquote;
				}
				case '/':
				CASE_TOKEN
				{
					buffer += msg.at(pos++);
					break;
				}
				case ',':
				{
					if (in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					if (key.size())
					{
						add_param(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_value(buffer);
					}

					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (key.size())
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_value(buffer);
					}

					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					key = buffer;
	
					buffer.clear();
					pos++;
					break;
				}
				case ' ':
				case '\t':
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (key.size())
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else if (buffer.size())
					{
						add_value(buffer);
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}

		return PROCEDURE_OK;
	}

	void HFBase_5_::generate_values()
	{
		char sym = ' ';
		values_ = challenge_;

		if (digest_cln_.empty())
			return;

		values_ += sym;

		std::ostringstream o;
		o << digest_cln_;

		values_ += o.str();

		remove_tail_symbol(sym);

		std::ostringstream p;
		p << header_params_;
		values_ += p.str();
	}

	int HFBase_5_::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_dquote = false;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				case '"':
				{
					in_dquote = !in_dquote;
				}
				CASE_TOKEN
				case ':':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '=':
				{
					key = buffer;

					pos++;
					buffer.clear();
					break;
				}
				case '\t':
				case ' ':
				{
					if (challenge_.size() || in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					if (buffer.size())
						challenge_ = buffer;

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
					if (key.size())
					{
						digest_cln_.append(key, buffer);
						key.clear();
					}
					else
					{
						digest_cln_.append(buffer, "");
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
					if (challenge_.empty())
					{
						challenge_ = buffer;
					}
					else if (key.size())
					{
						digest_cln_.append(key, buffer);
						key.clear();
					}
					else
					{
						digest_cln_.append(buffer, "");
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}
		return PROCEDURE_OK;
	}

	HFVia::HFVia() : HeaderField("Via", "v", true)
	{
//		header_params_.append("alias");
//		header_params_.append("branch");
//		header_params_.append("comp");
//		header_params_.append("keep");
//		header_params_.append("maddr");
//		header_params_.append("oc");
//		header_params_.append("oc-algo");
//		header_params_.append("oc-seq");
//		header_params_.append("oc-validity");
//		header_params_.append("received");
//		header_params_.append("rport");
//		header_params_.append("sigcomp-id");
//		header_params_.append("ttl");
	}

	void HFVia::generate_values()
	{
		std::ostringstream o;

		o << sent_proto_ << ' ' << sent_by_;

		if (header_params_.size())
			o << ";" << header_params_;

		values_ = o.str();
	}

	int HFVia::parse(std::string &msg, size_t &pos)
	{
		bool read_head_param = false, run = true;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				CASE_TOKEN
				case ':':
				case '/':
				{
					buffer += msg.at(pos++);
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
	
					buffer.clear();
				}
				case '\t':
				case '\r':
				{
					pos++;
					break;
				}
				case ';':
				{
					if (read_head_param)
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else
					{
						if (sent_by_.empty())
						{
							sent_by_ = buffer;
						}
						
						read_head_param = true;
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					key = buffer;
	
					pos++;
					buffer.clear();
					break;
				}
				case '\n':
				{
					if (read_head_param)
					{
						header_params_.append(key, buffer);
						key.clear();
					}
					else
					{
						if (sent_by_.empty())
						{
							sent_by_ = buffer;
						}
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "' :" << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}
		return PROCEDURE_OK;
	}

	HFContact::HFContact() : HFBase_1_("Contact", "m")
	{
//		header_params_.append("expires");
//		header_params_.append("mp");
//		header_params_.append("np");
//		header_params_.append("pub-gruu");
//		header_params_.append("q");
//		header_params_.append("rc");
//		header_params_.append("reg-id");
//		header_params_.append("temp-gruu");
//		header_params_.append("temp-gruu-cookie");
	}

	void HFRetryAfter::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFRetryAfter::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}


	void HFAlertInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFAlertInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFAllowEvents::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFAllowEvents::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFBase_1_::generate_values()
	{
		char sym = ',';
		std::ostringstream o;

		cons_.cleanup_empty_uri();

		for (auto &it : cons_)
		{
			o << *it << sym;
		}

		values_ = o.str();
		remove_tail_symbol(sym);

		if (header_params_.size())
		{
			std::ostringstream p;
			p << ";" << header_params_;
			values_ += p.str();
		}
	}


	void HFTimestamp::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFTimestamp::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFUserAgent::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFUserAgent::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFAnswerMode::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFAnswerMode::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFPrivAnswerMode::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFPrivAnswerMode::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFAcceptContact::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFAcceptContact::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	HFAuthorization::HFAuthorization() : HFBase_5_("Authorization")
	{
//		header_params_.append("algorithm");
//		header_params_.append("auts");
//		header_params_.append("cnonce");
//		header_params_.append("nc");
//		header_params_.append("nonce");
//		header_params_.append("opaque");
//		header_params_.append("qop");
//		header_params_.append("realm");
//		header_params_.append("response");
//		header_params_.append("uri");
//		header_params_.append("username");
	}

	HFCallInfo::HFCallInfo() : HFBase_1_("Call-Info", true)
	{
//		header_params_.append("m");
//		header_params_.append("purpose");
	}

	void HFCallInfo::generate_values()
	{
		char sym = ',';
		std::ostringstream o;

		cons_.cleanup_empty_uri();

		for (auto &it : cons_)
		{
			o << '<' << it->uri() << '>' << it->params() << sym;
		}

		values_ = o.str();

		remove_tail_symbol(sym);
	}

	int HFCallInfo::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_aquote = false, in_dquote = false;
		std::string buffer, key;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
			{
				case '"':
				{
					in_dquote = !in_dquote;
					buffer += msg.at(pos++);

					if (!in_dquote)
					{
						add_name(buffer);
						buffer.clear();
					}

					break;
				}
				CASE_TOKEN
				case '/':
				case '?':
				case ':':
				case '@':
				{
					buffer += msg.at(pos++);
					break;
				}
				case '<':
				{
					in_aquote = true;
					pos++;
					buffer.clear();
					break;
				}
				case '>':
				{
					in_aquote = false;

					if (buffer.size())
					{
						if (key.size())
						{
							add_param(key, buffer);
							key.clear();
						}
						else
						{
							add_uri(buffer);
						}
					}

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

					if (buffer.size())
					{
						if (key.size())
						{
							add_param(key, buffer);
							key.clear();
						}
						else
						{
							add_uri(buffer);
						}
					}

					pos++;
					buffer.clear();
					break;
				}
				case ';':
				{
					if (key.size())
					{
						add_param(key, buffer);
						key.clear();
					}
					else
					{
						if (buffer.size())
							add_uri(buffer);
					}
	
					pos++;
					buffer.clear();
					break;
				}
				case '=':
				{
					key = buffer;
	
					buffer.clear();
					pos++;
					break;
				}
				case ' ':
				{
					if (in_dquote)
					{
						buffer += msg.at(pos++);
						break;
					}

					if (in_aquote || key.size())
					{
						pos++;
						break;
					}

					buffer.clear();
				}
				case '\t':
				case '\r':
				{
					pos++;
					break;
				}
				case '\n':
				{
					if (key.size())
					{
						add_param(key, buffer);
						key.clear();
					}
					else
					{
						add_uri(buffer);
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}
		return PROCEDURE_OK;
	}

	HFEvent::HFEvent() : HeaderField("Event", "o")
	{
//		header_params_.append("adaptive-min-rate");
//		header_params_.append("body");
//		header_params_.append("call-id");
//		header_params_.append("effective-by");
//		header_params_.append("from-tag");
//		header_params_.append("id");
//		header_params_.append("include-session-description");
//		header_params_.append("max-rate");
//		header_params_.append("min-rate");
//		header_params_.append("model");
//		header_params_.append("profile-type");
//		header_params_.append("shared");
//		header_params_.append("to-tag");
//		header_params_.append("vendor");
//		header_params_.append("version");
	}

	void HFEvent::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFEvent::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFInReplyTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFInReplyTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFJoin::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFJoin::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFPrivacy::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFPrivacy::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	HFProxyAuthorization::HFProxyAuthorization() : HFBase_5_("Proxy-Authorization", true)
	{
//		header_params_.append("algorithm");
//		header_params_.append("auts");
//		header_params_.append("cnonce");
//		header_params_.append("nc");
//		header_params_.append("nonce");
//		header_params_.append("opaque");
//		header_params_.append("qop");
//		header_params_.append("realm");
//		header_params_.append("response");
//		header_params_.append("uri");
//		header_params_.append("username");
	}

	void HFPOSPAuthToken::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFPOSPAuthToken::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFPAssertedIdentity::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFPAssertedIdentity::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFPPreferredIdentity::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFPPreferredIdentity::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFReason::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFReason::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFReferTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFReferTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFReferredBy::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFReferredBy::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFReplyTo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFReplyTo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFReplaces::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFReplaces::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFRejectContact::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFRejectContact::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFRequestDisposition::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFRequestDisposition::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFRack::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFRack::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFSessionExpires::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFSessionExpires::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	HFSubscriptionState::HFSubscriptionState() : HeaderField("Subscription-State")
	{
//		header_params_.append("adaptive-min-rate");
//		header_params_.append("expires");
//		header_params_.append("max-rate");
//		header_params_.append("min-rate");
//		header_params_.append("reason");
//		header_params_.append("retry-after");
	}

	void HFSubscriptionState::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFSubscriptionState::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	HFAuthenticationInfo::HFAuthenticationInfo() : HeaderField("Authentication-Info")
	{
//		header_params_.append("cnonce");
//		header_params_.append("nc");
//		header_params_.append("nextnonce");
//		header_params_.append("qop");
//		header_params_.append("rspauth");
	}

	void HFAuthenticationInfo::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFAuthenticationInfo::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFMinSE::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFMinSE::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	HFProxyAuthenticate::HFProxyAuthenticate() : HFBase_4_("Proxy-Authenticate", true)
	{
//		header_params_.append("algorithm");
//		header_params_.append("domain");
//		header_params_.append("nonce");
//		header_params_.append("opaque");
//		header_params_.append("qop");
//		header_params_.append("realm");
//		header_params_.append("stale");
	}

	void HFWarning::generate_values()
	{
		char sym = ',';
		std::ostringstream o;

		for (auto &it : warn_vals_)
			o << it << sym;

		values_ = o.str();

		remove_tail_symbol(sym);
		
		std::stringstream p;
		p << header_params_;
		values_ += p.str();
	}

	int HFWarning::parse(std::string &msg, size_t &pos)
	{
		bool run = true, in_dquote = false;
		std::string buffer;
		size_t index = 0;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
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

					if (buffer.size())
					{
						if (index >= warn_vals_.size())
							warn_vals_.resize(warn_vals_.size()+1);

						if (warn_vals_.at(index).code_.empty())
							warn_vals_.at(index).code_ = buffer;
					}
				
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

					if (buffer.size())
					{
						if (index >= warn_vals_.size())
							warn_vals_.resize(warn_vals_.size()+1);

						if (warn_vals_.at(index).text_.empty())
							warn_vals_.at(index).text_ = buffer;
						index++;
					}

					pos++;
					buffer.clear();
					break;
				}
				case '"':
				{
					in_dquote = !in_dquote;

					if (!in_dquote)
					{
						if (buffer.size())
						{
							if (index >= warn_vals_.size())
								warn_vals_.resize(warn_vals_.size()+1);
	
							if (warn_vals_.at(index).text_.empty())
								warn_vals_.at(index).text_ = buffer;
							index++;
						}
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
					if (buffer.size())
					{
						if (index >= warn_vals_.size())
							warn_vals_.resize(warn_vals_.size()+1);

						if (warn_vals_.at(index).text_.empty())
							warn_vals_.at(index).text_ = buffer;
						index++;
					}

					if (pos+1 >= msg.size()) { run = false; break; }
					do_if_is_alpha(msg.at(pos+1), run = false)

					pos++;
					buffer.clear();
					break;
				}
				default:
				{
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}
		return PROCEDURE_OK;
	}

	HFWWWAuthenticate::HFWWWAuthenticate() : HFBase_5_("WWW-Authenticate", true)
	{
//		header_params_.append("algorithm");
//		header_params_.append("domain");
//		header_params_.append("nonce");
//		header_params_.append("opaque");
//		header_params_.append("qop");
//		header_params_.append("realm");
//		header_params_.append("stale");
	}

	void HFRSeq::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFRSeq::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFContentLanguage::generate_values()
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
	}

	int HFContentLanguage::parse(std::string &msg, size_t &pos)
	{
		std::cout << __PRETTY_FUNCTION__ << '\n';
		return PROCEDURE_OK;
	}

	void HFMIMEVersion::generate_values()
	{
		values_ = dotted_value_;
		std::stringstream p;
		p << header_params_;
		values_ += p.str();
	}

	int HFMIMEVersion::parse(std::string &msg, size_t &pos)
	{
		bool run = true;
		std::string buffer;

		while (msg.at(pos) == ' ' || msg.at(pos) == '\t') pos++;

		while (run)
		{
			switch (msg.at(pos))
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
					std::cerr << __PRETTY_FUNCTION__ << " Unexpected '" << msg.at(pos) << '(' << (int)msg.at(pos) << ')' << "': " << buffer << "\n";
					pos++;
					buffer.clear();
				}
			}
		}
		return PROCEDURE_OK;
	}

	void HeaderFields::init_allowed_fields()
	{
		allowed_fields_["Call-ID"]           	= HF_CALLID;
		allowed_fields_["CSeq"]             	= HF_CSEQ;
		allowed_fields_["From"]             	= HF_FROM;
		allowed_fields_["To"]               	= HF_TO;
		allowed_fields_["Via"]              	= HF_VIA;
		allowed_fields_["Alert-Info"]       	= HF_ALERT_INFO;
		allowed_fields_["Allow-Events"]     	= HF_ALLOW_EVENTS;
		allowed_fields_["Date"]             	= HF_DATE;
		allowed_fields_["Contact"]          	= HF_CONTACT;
		allowed_fields_["Organization"]     	= HF_ORGANIZATION;
		allowed_fields_["Record-Route"]     	= HF_RECORD_ROUTE;
		allowed_fields_["Retry-After"]      	= HF_RETRY_AFTER;
		allowed_fields_["Subject"]          	= HF_SUBJECT;
		allowed_fields_["Supported"]        	= HF_SUPPORTED;
		allowed_fields_["Timestamp"]        	= HF_TIMESTAMP;
		allowed_fields_["User-Agent"]       	= HF_USER_AGENT;
		allowed_fields_["Answer-Mode"]      	= HF_ANSWER_MODE;
		allowed_fields_["Priv-Answer-Mode"] 	= HF_PRIV_ANSWER_MODE;
		allowed_fields_["Accept"]           	= HF_ACCEPT;
		allowed_fields_["Accept-Contact"]   	= HF_ACCEPT_CONTACT;
		allowed_fields_["Accept-Encoding"]  	= HF_ACCEPT_ENCODING;
		allowed_fields_["Accept-Language"]  	= HF_ACCEPT_LANGUAGE;
		allowed_fields_["Authorization"]    	= HF_AUTHORIZATION;
		allowed_fields_["Call-Info"]        	= HF_CALL_INFO;
		allowed_fields_["Event"]            	= HF_EVENT;
		allowed_fields_["In-Reply-To"]      	= HF_IN_REPLY_TO;
		allowed_fields_["Join"]             	= HF_JOIN;
		allowed_fields_["Priority"]         	= HF_PRIORITY;
		allowed_fields_["Privacy"]          	= HF_PRIVACY;
		allowed_fields_["Proxy-Authorization"]	= HF_PROXY_AUTHORIZATION;
		allowed_fields_["Proxy-Require"]    	= HF_PROXY_REQUIRE;
		allowed_fields_["P-OSP-AuthToken"]  	= HF_P_OSP_AUTHTOKEN;
		allowed_fields_["PAsserted-Identity"]	= HF_PASSERTED_IDENTITY;
		allowed_fields_["PPreferred-Identity"]	= HF_PPREFERRED_IDENTITY;
		allowed_fields_["Max-Forwards"]     	= HF_MAX_FORWARDS;
		allowed_fields_["Reason"]           	= HF_REASON;
		allowed_fields_["Refer-To"]         	= HF_REFER_TO;
		allowed_fields_["Referred-By"]      	= HF_REFERRED_BY;
		allowed_fields_["Reply-To"]         	= HF_REPLY_TO;
		allowed_fields_["Replaces"]         	= HF_REPLACES;
		allowed_fields_["Reject-Contact"]   	= HF_REJECT_CONTACT;
		allowed_fields_["Request-Disposition"]	= HF_REQUEST_DISPOSITION;
		allowed_fields_["Require"]          	= HF_REQUIRE;
		allowed_fields_["Route"]            	= HF_ROUTE;
		allowed_fields_["Rack"]             	= HF_RACK;
		allowed_fields_["Session-Expires"]  	= HF_SESSION_EXPIRES;
		allowed_fields_["Subscription-State"]	= HF_SUBSCRIPTION_STATE;
		allowed_fields_["AuthenticationInfo"]	= HF_AUTHENTICATIONINFO;
		allowed_fields_["Error-Info"]       	= HF_ERROR_INFO;
		allowed_fields_["Min-Expires"]      	= HF_MIN_EXPIRES;
		allowed_fields_["Min-SE"]           	= HF_MIN_SE;
		allowed_fields_["Proxy-Authenticate"]	= HF_PROXY_AUTHENTICATE;
		allowed_fields_["Server"]           	= HF_SERVER;
		allowed_fields_["Unsupported"]      	= HF_UNSUPPORTED;
		allowed_fields_["Warning"]          	= HF_WARNING;
		allowed_fields_["WWW-Authenticate"] 	= HF_WWW_AUTHENTICATE;
		allowed_fields_["RSeq"]             	= HF_RSEQ;
		allowed_fields_["Allow"]            	= HF_ALLOW;
		allowed_fields_["Content-Encoding"] 	= HF_CONTENT_ENCODING;
		allowed_fields_["Content-Length"]   	= HF_CONTENT_LENGTH;
		allowed_fields_["Content-Disposition"] 	= HF_CONTENT_DISPOSITION;
		allowed_fields_["Content-Language"] 	= HF_CONTENT_LANGUAGE;
		allowed_fields_["Content-Type"]     	= HF_CONTENT_TYPE;
		allowed_fields_["Expires"]          	= HF_EXPIRES;
		allowed_fields_["MIME-Version"]     	= HF_MIME_VERSION;
   	}

	HeaderFields::HeaderFields()
	{
	}

	HeaderFields::~HeaderFields()
    {
	}

} // namespace EasySip
