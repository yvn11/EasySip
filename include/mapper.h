#pragma once

#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>

namespace EasySip
{
	typedef std::vector<std::string> Values;
	typedef std::map<std::string, std::string> ValueMap;

	struct CodeMap : public std::pair<int, std::string>
	{
		int Code()
		{
			return first;
		}

		std::string Name() const
		{
			return second;
		}

		void Code(int c)
		{
			first = c;
		}

		void Name(std::string n)
		{
			second = n;
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

		bool operator< (CodeMap cm)
		{
			return (first < cm.first);
		}
	
		void operator= (const CodeMap &cm)
		{
			first = cm.first;
			second = cm.second;
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

	struct Parameter : public std::pair<std::string, std::string>
	{
		bool need_value_;

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

		std::string Value()
		{
			return second;
		}

		void Name(std::string n)
		{
			first = n;
		}

		void Value(std::string v)
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

			if (p.need_value_)
			{
				o << "=";

				if (p.Value().size())
					o << p.Value();
			}

			return o;
		}
	};

	class Parameters : std::set<Parameter>
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

		bool has_Name(std::string name)
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

		friend std::ostream& operator<< (std::ostream &o, Parameters ps)
		{
			if (ps.empty())
				return o;

			o << ";";

			for (Parameters::iterator it = ps.begin(); it != ps.end(); it++)
			{
				o << *it;

				if (std::distance(ps.begin(), it) < (int)ps.size())
					o << ";";
			}

			return o;
		}
	};
} // namespace EasiSip
