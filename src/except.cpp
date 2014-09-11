/*
 * src/except.cpp
 * 
 * Author: Zex <top_zlynch@yahoo.com>
 */
#include "except.h"

namespace EasySip
{
	const char* Except::what()
	{
		return msg_.c_str();
	}
} // namespace EasySip
