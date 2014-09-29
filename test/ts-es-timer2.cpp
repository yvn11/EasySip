#include "timer.h"
#include <thread>

using namespace EasySip;

int main()
{
	Timer t2(5, 0);
	t2.start();

	char c;
	std::cin.get(c);

	return 0;
}

