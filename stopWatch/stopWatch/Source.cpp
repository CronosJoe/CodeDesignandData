#include "stopwatch.h"



stopwatch::stopwatch()

{

	reset();

}



void stopwatch::start()

{

	lastStartTime = std::chrono::high_resolution_clock::now();

}



void stopwatch::stop()

{

	auto diff = std::chrono::high_resolution_clock::now() - lastStartTime;

	totalMilliseconds += std::chrono::duration_cast<std::chrono::milliseconds>(diff);

}



double stopwatch::millisecondCount()

{

	return totalMilliseconds.count();

}



double stopwatch::secondsCount()

{

	return std::chrono::duration_cast<std::chrono::seconds>(totalMilliseconds).count();

}



void stopwatch::reset()

{

	totalMilliseconds = std::chrono::milliseconds();

}