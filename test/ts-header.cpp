#include "../include/header_field.h"
#include <iostream>

using namespace EasySip;

int main()
{
	std::cout << HFFrom().Field()<< '\n';
	return 0;
}
