#include <iostream>



#include "stopwatch.h"



#include <thread>

#include <chrono>



void bubbleSort(int* numbers, size_t numbersLength)

{

	bool swapped = true;

	while (swapped)
	{
		swapped = false;
		//more efficient to flip this until it doesn't flip anymore then to do an additional round of checks to flip bool once
		for (size_t i = 1; i < numbersLength; ++i)
		{
			if (numbers[i - 1] > numbers[i])
			{
				int temp = numbers[i - 1];
				// swap
				numbers[i - 1] = numbers[i];
				numbers[i] = temp;
				swapped = true;
			}
		}
	}
}


int main()
{
	stopwatch demoTimer;
	int numbersLength = 500;
	int* numbers = new int[numbersLength];
	for (size_t i = 0; i < numbersLength; ++i)
	{
		numbers[i] = i;
	}



	std::cout << "number generation done" << std::endl;



	demoTimer.start();



	bubbleSort(numbers, numbersLength);



	demoTimer.stop();



	std::cout << demoTimer.millisecondCount() << std::endl;

	std::cout << demoTimer.secondsCount() << std::endl;



	return 0;

}