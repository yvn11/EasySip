#include "thread.h"

using namespace EasySip;

void* t1_loop(void* arg)
{
	int a = *(int*)arg;

	std::cout << a << '\n';

	return 0;
}

class X
{
	int num;
public:
	X(int n) : num(n) {};

	void* show()
	{
		std::cout << num << '\n';

	std::cout << "start " << pthread_yield() << '\n';
		return 0;
	}
};


int main()
{
	int arg = 1098;
	X x(132);
	//Thread t1(t1_loop, (void*)&arg);
	Thread t1 = Thread(&X::show, &x);

//	t1.join();


	char c;
	std::cin.get(c);

	return 0;
}
