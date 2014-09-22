/*
 * include/utils.h
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#pragma once

#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <iostream>

namespace EasySip
{
	template<typename T>
	T& RefOf(T& t) { return t; }

	template<typename T>
	class PtsOf : public std::vector<T*>
	{
	public:
		PtsOf()
		{
		}

		void append_item()
		{
			this->push_back(new T);
		}

		T* last()
		{
			return this->at(this->size()-1);
		}
	};

	class CodeMap : public std::pair<int, std::string>
	{
	public:

		void Code(int c)
		{
			first = c;
		}

		void name(std::string n)
		{
			second = n;
		}

	public:

		int Code() const
		{
			return first;
		}

		std::string name() const
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

} // namespace EasiSip
