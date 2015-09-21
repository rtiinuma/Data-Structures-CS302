#include "Timer.h"
#include <iostream>

using namespace std;

int main()
{
	Timer testTimer;
	int numTests = 1000000;
	double max = 0, min = 0;
	double total = 0.0;
	double measuredTime;
	double avg;

	// Get data for first run
	testTimer.start();
	testTimer.stop();
	measuredTime = testTimer.getElapsedTime();
	max = min = measuredTime;
	total = measuredTime;
	cout << "Measured time for first trial: " << measuredTime << endl;

	for( int i = 0; i < numTests; i++ )
	{
		testTimer.start();
		testTimer.stop();
		measuredTime = testTimer.getElapsedTime();
		if( measuredTime < min )
		{
			min = measuredTime;
		}
		if( measuredTime > max )
		{
			max = measuredTime;
		}
		total += measuredTime;
	}
	
	avg = total / numTests;
	cout << "Average time for " << numTests << " trials = " << avg << endl;
	cout << "Max time: " << max << endl;
	cout << "Min time: " << min << endl;


}
