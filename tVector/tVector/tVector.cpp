// tVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "tVector.h"


int main()
{
	tVector<int> numbers;
	numbers.~tVector();
	for (auto it = numbers.begin(); it != numbers.end(); ++it)
	{
		std::cout << (*it) << std::endl; //this should work using *it but the reference isn't working this way? Do I need a new operator method
	}
	return 0;
}
