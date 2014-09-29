#include "timer.h"
#include <thread>

using namespace EasySip;

void startt(Timer *t)
{
	t->start();
}


int main()
{
	Timer t1(3, 0);
	Timer t2(5, 0);
//	t1.start();

	std::thread th1(startt, &t1);
	std::thread th2(startt, &t2);

	th1.join();
	th2.join();


	char c;
	std::cin.get(c);

	return 0;
}
