/*
 * include/parameter.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include "utils.h"
#include "except.h"

namespace EasySip
{
	class Parameter : public std::pair<std::string, std::string>
	{
	public:
		Parameter()
		{
		}

		Parameter(std::string name, std::string value = "")
		{
			first = name;
			second = value;
		}

		~Parameter()
		{
		}

		std::string name() const
		{
			return first;
		}

		std::string value() const
		{
			return second;
		}

		void name(const std::string n)
		{
			first = n;
		}

		void value(const std::string v)
		{
			second = v;
		}

		friend bool operator< (Parameter a, Parameter b)
		{
			return a.name() < b.name();
		}

		friend std::ostream& operator<< (std::ostream &o, Parameter p)
		{
			o << p.name();
	
			if (p.value().size())
			{
				o << "=" << p.value();
			}
	
			return o;
		}
	};

	class Parameters : public std::vector<Parameter>
	{
		std::string sym_;

	public:

		Parameters(std::string sym) : sym_(sym)
		{
		}

		Parameters() : sym_(";")
		{
		}

		~Parameters()
		{
		}

		void Sym(std::string sym)
		{
			sym_ = sym;
		}

		std::string Sym() const
		{
			return sym_;
		}

		void append(std::string name, std::string value)
		{
			if (!has_name(name))
				push_back(Parameter(name, value));
		}

		void append(std::string name)
		{
			append(name, "");
		}
	
		bool has_name(std::string name)
		{
			for (auto &it : *this)
			{
				if (name == it.first)
					return true;
			}
	
			return false;
		}

		void set_value_by_name(std::string name, std::string value)
		{
			for (auto &it : *this)
			{
				if (name == it.first)
				{
					it.second = value;
					return;
				}
			}

			append(name, value);
		}

		std::string get_value_by_name(std::string name)
		{
			for (auto it : *this)
			{
				if (it.first == name)
					return it.second;
			}

			return std::string();
		}
	
		friend std::ostream& operator<< (std::ostream &o, Parameters &ps)
		{
			for (Parameters::iterator it = ps.begin(); it != ps.end(); it++)
			{
				if (std::distance(ps.begin(), it) < (int)ps.size())
					o << ps.Sym();
	
				o << *it;
			}
	
			return o;
		}
	};

	struct ItemWithParams
	{
		std::vector<std::string> items_;
		Parameters params_;

		ItemWithParams()
		{
		}

		ItemWithParams(std::string item)
		{
			items_.push_back(item);
		}

		Parameters& params()
		{
			return params_;
		}

		friend std::ostream& operator<< (std::ostream &o, ItemWithParams &c)
		{
			for (auto &it : c.items_)
				o << it;

			o << c.params_;

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

		bool has_param(std::string name)
		{
			return params_.has_name(name);
		}
	};
} // namespace EasiSip
