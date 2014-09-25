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

		bool empty()
		{
			return (name().empty() && uri().empty());
		}

		bool full()
		{
			return (!uri().empty() && !name().empty());
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
