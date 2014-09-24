#include <iostream>
#include <string.h>
#include <memory>
#include <locale>
#include <unordered_map>
#include <algorithm>

class A
{
	unsigned long value;
public:
	A(A &a)
	: value(a.Value())
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}
	A()
	: value(3)
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}
	A(unsigned int val)
	{
		value = val;
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}
	void show()
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
	}
	~A()
	{}

	void Value(unsigned long val)
	{
		value = val;
	}

	unsigned long Value()
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
		return value;
	}

	unsigned long operator* (unsigned long val)
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
		return (value*val);
	}

	A operator= (A a)
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
		A ret(a.Value());
		return ret;
	}

	friend std::ostream& operator<< (std::ostream &o, A a)
	{
		o << __PRETTY_FUNCTION__ << "\n";
		return o;
	}
//	void operator() (A a)
//	{
//		std::cout << __PRETTY_FUNCTION__ << "\n";
//		A ret(a.Value());
//		return ret;
//	}

};

class B : public A
{
public:
	B(unsigned int val)
	: A(val)
	{
		std::cout << __PRETTY_FUNCTION__ << "\n";
		show();
	}

	~B()
	{}

	int operator[] (int val)
	{
		return 3310;
	}

	int operator[] (std::string hello)
	{
		return 928;
	}
	int operator[] (A a)
	{
		a.show();
		return 309;
	}
};

	#define STRDQUOTE "'""\"""'"
	#define STRQUOTE "'""\'""'"
	#define STRBSLASH "'""\\""'"



int main()
{
//	B b(100);
	B b2(B(100)*3);
//	std::cout << b.Value() << '\n';
	std::cout << b2.Value() << '\n';
	std::cout << b2[3] << '\n';
	std::cout << b2["ok"] << '\n';
	A a(333);
	std::cout << b2[a] << '\n';

	std::shared_ptr<A> p;
	p = std::make_shared<A>();
	p->show();

	std::unordered_map<std::string, std::string> buck;

	buck["hello"] = "now";
	std::string hstr("hello");

	std::cout << buck.hash_function()(hstr) << '\n';

	std::vector<int> digits, buf;

	for (int i = 0; i < 10; i++)
	{
		buf.push_back(i);
	}

	digits = buf;
	std::reverse(digits.begin(), digits.end());

	for (auto &i : digits)
		std::cout << i << ';';

	digits.insert(digits.end(), buf.begin(), buf.end());

	for (auto &i : digits)
		std::cout << i << ';';
	return 1;
}


