/*
 * include/uri.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <memory>
#include <locale>
#include "parameter.h"
#include <iostream>

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

	class Contact : public ItemWithParams
	{
	public:
		Contact()
		{
			items_.resize(2);
		}

		Contact(std::string name, std::string uri)
		{
			items_.push_back(name);
			items_.push_back(uri);
		}

		std::string& name()
		{
			return items_.at(0);
		}

		std::string& uri()
		{
			return items_.at(1);
		}

		void name(std::string name)
		{
			items_.at(0) = name;
		}

		void uri(std::string uri)
		{
			items_.at(1) = uri;
		}

		friend std::ostream& operator<< (std::ostream &o, Contact &c)
		{
			if (c.name().size() || c.params().size())
				o << c.name() << " <";

			o << c.uri() << c.params();

			if (c.name().size() || c.params().size())
				o << ">";

			return o;
		}

	};

	struct ContactList : public PtsOf<Contact>
	{
		void cleanup_empty_uri()
		{
			for (iterator it = begin(); it != end();)
			{
				if ((*it)->uri().empty())
					erase(it);
				else
					it++;
			}
		}

		void append(std::string uri, std::string name = "")
		{
			if (uri.empty()) return;

			append_item();
			last()->uri(uri);

			if (name.size())
				last()->name(name);
		}

		void append(ContactList& c)
		{
			insert(end(), c.begin(), c.end());
		}

		void append(ContactList::iterator from, ContactList::iterator to)
		{
			insert(end(), from, to);
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
