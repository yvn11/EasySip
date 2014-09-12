#include <iostream>
#include "ts-thr-timer.h"

void on_timeup()
{
	std::cout << __PRETTY_FUNCTION__ << '\n';
}

typedef void (*func_cb)();

int main()
{
	int i=1000;
	timer<int, func_cb>(i, &on_timeup);

	while(1);

	return 0;
}

