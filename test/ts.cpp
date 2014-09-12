#include <iostream>
#include <string.h>
#include <memory>

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


//	char buf;
//
//	while (std::getline(std::cin, line))
//	{
//		strncpy(&buf, line.c_str(), 1);
//		buffer += buf;
//		std::cout << buffer << '\n';
//	}

	std::string msg_ = "123InVITEHEL86OAKJF35\nSG48HBBasdlfkj83439 k";
//		std::string get_respond_code()
		{
			size_t pos, next;

			std::cout << "[" << msg_ << "]\n";

			for (next = pos = 0; next != std::string::npos; pos = next+1)
			{
				next = msg_.find_first_of(' ', pos);
				std::cout << pos << ' ' << next << "|" << msg_.substr(pos, next-pos) << "|\n";
			}
		}

	switch (1)
	{
		case (1):
			std::cout << "he---\n";
			break;
		case (3):
			std::cout << "no\n";
	}

	std::shared_ptr<A> p;
	p = std::make_shared<A>();
	p->show();
	std::cout << "--------------" << (p == 0) << '\n' << *p;

	return 1;
}


