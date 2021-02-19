#include <iostream>
#include "LinkedList.h"
using namespace std;
int main()
{
	tList<int> numbers = tList<int>();
	numbers.push_front(1);
	numbers.push_front(2);
	numbers.push_front(3);
	numbers.push_front(4);
	numbers.print();
	numbers.print();
	return 0;
}