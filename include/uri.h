/*
 * include/uri.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <memory>
#include "mapper.h"

namespace EasySip
{
	typedef Parameters URIParams;
	typedef Parameters HeaderParams;

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
			if (!uri.uri_.empty())
				o << "<" << uri.uri_ << uri.uri_params_ << ">";
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
			uri_params_.append("aai");
			uri_params_.append("bnc");
			uri_params_.append("cause");
			uri_params_.append("ccxml");
			uri_params_.append("comp");
			uri_params_.append("gr");
			uri_params_.append("locale");
			uri_params_.append("lr", false);
			uri_params_.append("m");
			uri_params_.append("maddr");
			uri_params_.append("maxage");
			uri_params_.append("maxstale");
			uri_params_.append("method");
			uri_params_.append("ob");
			uri_params_.append("postbody");
			uri_params_.append("repeat");
			uri_params_.append("sg");
			uri_params_.append("sigcomp-id");
			uri_params_.append("target");
			uri_params_.append("transport");
			uri_params_.append("ttl");
			uri_params_.append("user");
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
