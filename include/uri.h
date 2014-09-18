/*
 * include/uri.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <memory>
#include <locale>
#include "parameter.h"

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

	#define do_if_is_alpha(c, f) 	\
	{								\
		std::locale loc;			\
		if (std::isalpha(c, loc)) { f; }	\
	}

	struct Contact
	{
		std::string name_;
		std::string uri_;
		Parameters params_;

		Contact()
		{
		}

		Contact(std::string name, std::string uri)
		: name_(name), uri_(uri)
		{
		}

		friend std::ostream& operator<< (std::ostream &o, Contact &c)
		{
			if (c.name_.size() || c.params_.size())
				o << c.name_ << " <";

			o << c.uri_ << c.params_;

			if (c.name_.size() || c.params_.size())
				o << ">";

			return o;
		}

		void set_param(std::string name, std::string value)
		{
			params_.set_value_by_name(name, value);
		}

		void add_param(std::string name, std::string value = "")
		{
			params_.append(name, value);
		}
	};

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
//			// RFC-4240
//			uri_params_.append("content-type");
//			uri_params_.append("delay");
//			uri_params_.append("duration");
//			uri_params_.append("extension");
//			uri_params_.append("param");
//			uri_params_.append("play");
//			uri_params_.append("voicexml");


} // namespace EasySip
