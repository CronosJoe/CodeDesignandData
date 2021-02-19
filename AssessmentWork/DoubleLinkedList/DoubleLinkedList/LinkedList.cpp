#include <iostream>
#include "LinkedList.h"
using namespace std;
int main()
{
	tList<int> numbers = tList<int>();
	numbers.push_back(5);
	numbers.print();
	return 0;
}