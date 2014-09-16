/*
 * include/uri.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <memory>
#include <locale>
#include "mapper.h"

namespace EasySip
{
	#define CASE_UPPER_ALPHA \
				case 'A': \
				case 'B': \
				case 'C': \
				case 'D': \
				case 'E': \
				case 'F': \
				case 'G': \
				case 'H': \
				case 'I': \
				case 'J': \
				case 'K': \
				case 'L': \
				case 'M': \
				case 'N': \
				case 'O': \
				case 'P': \
				case 'Q': \
				case 'R': \
				case 'S': \
				case 'T': \
				case 'U': \
				case 'V': \
				case 'W': \
				case 'X': \
				case 'Y': \
				case 'Z':
	#define CASE_LOWER_ALPHA \
				case 'a': \
				case 'b': \
				case 'c': \
				case 'd': \
				case 'e': \
				case 'f': \
				case 'g': \
				case 'h': \
				case 'i': \
				case 'j': \
				case 'k': \
				case 'l': \
				case 'm': \
				case 'n': \
				case 'o': \
				case 'p': \
				case 'q': \
				case 'r': \
				case 's': \
				case 't': \
				case 'u': \
				case 'v': \
				case 'w': \
				case 'x': \
				case 'y': \
				case 'z':

	#define CASE_ALPHA \
			CASE_UPPER_ALPHA \
			CASE_LOWER_ALPHA 

	#define CASE_DIGIT \
				case '1': \
				case '2': \
				case '3': \
				case '4': \
				case '5': \
				case '6': \
				case '7': \
				case '8': \
				case '9': \
				case '0': 

	#define CASE_ALPHA_NUM \
			CASE_ALPHA \
			CASE_DIGIT 

	#define CASE_TOKEN \
				CASE_ALPHA_NUM \
				case '-': \
				case '.': \
				case '!': \
				case '%': \
				case '*': \
				case '_': \
				case '+': \
				case 39: \
				case '~':

	#define CASE_WORD \
				CASE_TOKEN \
				case '(': \
				case ')': \
				case '<': \
				case '>': \
				case ':': \
				case 92: \
				case 34: \
				case '/': \
				case '[': \
				case ']': \
				case '?': \
				case '{': \
				case '}': 

	typedef Parameters URIParams;
	typedef Parameters HeaderParams;

	#define do_if_is_alpha(c, f) 	\
	{								\
		std::locale loc;			\
		if (std::isalpha(c, loc)) { f; }	\
	}

	#define do_if_is_linefeed(c, f)	\
	{								\
		if (c == '\n') { f; }		\
	}

	struct URI
	{
		std::string uri_;
		URIParams uri_params_;

		URI()
		{
			Initialize();
		}

		~URI()
		{
		}

		// set value of exist parameter pair
		void set_param(std::string name, std::string value)
		{
			uri_params_.set_value_by_name(name, value);
		}

		// create new parameter
		void add_param(std::string name, std::string value = "", bool need_value = true)
		{
			uri_params_.append(name, value, need_value);
		}

		friend std::ostream& operator<< (std::ostream &o, URI uri)
		{
			if (uri.uri_.empty()) return o;

			URIParams::iterator it = uri.uri_params_.begin();

			for (; it != uri.uri_params_.end(); it++)
				if (!(it->Value().empty()))
					break;

			if (it != uri.uri_params_.end())
			{
				o << "<" << uri.uri_ << ">";
			}
			else
			{
				o << uri.uri_ << uri.uri_params_;
			}

			return o;
		}

		std::string operator() ()
		{
			std::ostringstream o;
			o << *this;

			return o.str();
		}

		void Initialize()
		{
//			uri_params_.append("aai");
//			uri_params_.append("bnc");
//			uri_params_.append("cause");
//			uri_params_.append("ccxml");
//			uri_params_.append("comp");
//			uri_params_.append("gr");
//			uri_params_.append("locale");
//			uri_params_.append("lr", false);
//			uri_params_.append("m");
//			uri_params_.append("maddr");
//			uri_params_.append("maxage");
//			uri_params_.append("maxstale");
//			uri_params_.append("method");
//			uri_params_.append("ob");
//			uri_params_.append("postbody");
//			uri_params_.append("repeat");
//			uri_params_.append("sg");
//			uri_params_.append("sigcomp-id");
//			uri_params_.append("target");
//			uri_params_.append("transport");
//			uri_params_.append("ttl");
//			uri_params_.append("user");
			// RFC-4240
//			uri_params_.append("content-type");
//			uri_params_.append("delay");
//			uri_params_.append("duration");
//			uri_params_.append("extension");
//			uri_params_.append("param");
//			uri_params_.append("play");
//			uri_params_.append("voicexml");
		}

	};


} // namespace EasySip
