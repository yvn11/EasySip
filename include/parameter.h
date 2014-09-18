/*
 * include/parameter.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sstream>
#include <set>
#include <map>
#include <vector>
#include "except.h"

namespace EasySip
{
	template<typename T>
	T& RefOf(T& t) { return t; }

	class CodeMap : public std::pair<int, std::string>
	{
	public:

		void Code(int c)
		{
			first = c;
		}

		void Name(std::string n)
		{
			second = n;
		}

	public:

		int Code() const
		{
			return first;
		}

		std::string Name() const
		{
			return second;
		}

		CodeMap()
		{
		}

		CodeMap(int c)
		{
			first = c;
		}
	
		CodeMap(std::string n)
		{
			second = n;
		}

		CodeMap(int c, std::string n)
		{
			first = c;
			second = n;
		}

		std::string CodeStr() const
		{
			std::ostringstream o;
			o << first;
			return o.str();
		}

		bool operator< (CodeMap cm)
		{
			return (first < cm.first);
		}
	
		CodeMap& operator= (const CodeMap &cm)
		{
			first = cm.first;
			second = cm.second;
			return *this;
		}

		CodeMap& operator= (CodeMap &cm)
		{
			first = cm.first;
			second = cm.second;
			return *this;
		}


		bool operator== (const CodeMap &cm)
		{
			return ((first == cm.first ) && (second == cm.second));
		}

		friend std::ostream& operator<< (std::ostream &o, CodeMap cm)
		{
			o << cm.first << " " << cm.second;
			return o;
		}

		std::string operator() ()
		{
			std::ostringstream o;
			o << first << " " << second << '\n';
			return o.str();
		}

		void operator() (CodeMap &cm)
		{
			*this = cm;
		}
	};

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

		std::string Name() const
		{
			return first;
		}

		std::string Value() const
		{
			return second;
		}

		void Name(const std::string n)
		{
			first = n;
		}

		void Value(const std::string v)
		{
			second = v;
		}

		friend bool operator< (Parameter a, Parameter b)
		{
			return a.Name() < b.Name();
		}

		friend std::ostream& operator<< (std::ostream &o, Parameter p)
		{
			o << p.Name();
	
			if (p.Value().size())
			{
				o << "=" << p.Value();
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

		void append(std::string name)
		{
			push_back(Parameter(name, ""));
		}
	
		void append(std::string name, std::string value)
		{
			push_back(Parameter(name, value));
		}
	
		bool has_name(std::string name)
		{
			for (auto &it : *this)
				if (name == it.first)
					return true;
	
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
			iterator it;
	
			for (it = begin(); it != end(); it++)
				if (name == it->first)
					break;
	
			if (it == end())
				return std::string();

			return it->second;	
		}
	
		friend std::ostream& operator<< (std::ostream &o, Parameters &ps)
		{
			for (Parameters::iterator it = ps.begin(); it != ps.end(); it++)
			{
				if (std::distance(ps.begin(), it) <= (int)ps.size()-1)
					o << ps.Sym();
	
				o << *it;
			}
	
			return o;
		}
	};
} // namespace EasiSip
