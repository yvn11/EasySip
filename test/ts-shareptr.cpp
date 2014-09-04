#include <iostream>
#include <memory>

class A
{
public:
	int n_;
	A(int n) : n_(n)
	{ std::cout << n_ << " construct\n"; }
	~A()
	{ std::cout << n_ << " destruct\n"; }
};
int main()
{
	std::shared_ptr<A> a;

	a = std::make_shared<A>(3);
	std::cout << a->n_ << ">>>>>>>>\n";
	a = std::make_shared<A>(100);
	std::cout << a->n_ << ">>>>>>>>\n";

	return 0;
}
