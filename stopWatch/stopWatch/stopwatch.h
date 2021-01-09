#pragma once



#include <chrono>



class stopwatch

{

	// Total number of milliseconds elapsed with this stopwatch

	std::chrono::milliseconds totalMilliseconds;



	// The time at which the stopwatch was last started

	std::chrono::high_resolution_clock::time_point lastStartTime;



public:

	// Initializing the stopwatch

	stopwatch();



	// Start it

	void start();



	// Stop it (and update the total time)

	void stop();



	// Return the number of milliseconds recorded

	double millisecondCount();



	// Return the number of seconds recorded by this stopwatch

	double secondsCount();



	// Clear the stopwatch, zeroing out any time accumulated

	void reset();

};