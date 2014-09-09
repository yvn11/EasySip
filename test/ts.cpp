#include <iostream>
#include <string.h>

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
};

int main()
{
//	B b(100);
	B b2(B(100)*3);
//	std::cout << b.Value() << '\n';
	std::cout << b2.Value() << '\n';


		std::string buffer, line;
//
//		while(std::getline(std::cin, line))
//		{
//			buffer += line;
//		}
//
//		std::cout <<  "---------------\n"
//			<< buffer;
//		std::cout <<  "---------------\n";
//
//	std::cout << ";;;;;;;;;;;;;;;;;;;;;;;\n";


	char buf;

	while (std::getline(std::cin, line))
	{
		strncpy(&buf, line.c_str(), 1);
		buffer += buf;
		std::cout << buffer << '\n';
	}

	return 1;
}


