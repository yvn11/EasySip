/*
 * include/mapper.h
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

	typedef std::vector<std::string> Values;
	typedef std::map<std::string, std::string> ValueMap;

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

	typedef std::vector<std::string> Values;
	typedef std::map<std::string, std::string> ValueMap;

	class Parameter : public std::pair<std::string, std::string>
	{
		bool need_value_;

	public:
		Parameter() : need_value_(true)
		{
		}

		Parameter(std::string name, std::string value = "", bool need_value = true)
		{
			first = name;
			second = value;
			need_value_ = need_value;
		}

		~Parameter()
		{
		}

		std::string Name()
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
	
			if (p.need_value_ && p.Value().size())
			{
				o << "=" << p.Value();
			}
	
			return o;
		}
	};

	class Parameters : public std::set<Parameter>
	{
	public:

		Parameters()
		{
		}

		~Parameters()
		{
		}

		void append(std::string name, bool need_value)
		{
			Parameter p(name, "", true);
			insert(p);
		}
	
		void append(std::string name, std::string value = "", bool need_value = true)
		{
			Parameter p(name, value, need_value);
			insert(p);
		}
	
		bool has_name(std::string name)
		{
			Parameter p(name);
	
			return (find(p) == end() ? false : true);
		}
	
		void set_value_by_name(std::string name, std::string value)
		{
			iterator it;
	
			for (it = begin(); it != end(); it++)
				if (name == it->first)
					break;
	
			if (it == end())
				return; // TODO: throw error
	
			erase(it);
			append(name, value);
		}

		std::string get_value_by_name(std::string name)
		{
			iterator it;
	
			for (it = begin(); it != end(); it++)
				if (name == it->first)
					break;
	
			if (it == end())
				return std::string(); // TODO: throw error

			return it->second;	
		}
	
		friend std::ostream& operator<< (std::ostream &o, Parameters &ps)
		{
			if (ps.empty())
				return o;
	
			for (Parameters::iterator it = ps.begin(); it != ps.end(); it++)
			{
				if (it->Value().empty())
					continue;
	
				if (std::distance(ps.begin(), it) <= (int)ps.size()-1)
					o << ";";
	
				o << *it;
	
			}
	
			return o;
		}
	};
} // namespace EasiSip
