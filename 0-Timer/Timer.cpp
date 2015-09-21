// Timer.cpp

#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"
#include <sys/time.h>

Timer::Timer() {
	beginTime.tv_sec = 0;
	beginTime.tv_usec = 0;
	duration.tv_sec = 0;
	duration.tv_usec = 0;
	timerWasStarted = false;
}

void Timer::start() throw (runtime_error) {

   
	gettimeofday( &beginTime, NULL );
	timerWasStarted = true;
}

void Timer::stop() throw (logic_error){
	if( timerWasStarted )
	{
    		gettimeofday( &duration, NULL );
	}
	else
	{
		throw logic_error("");
	}
}

double Timer::getElapsedTime() const throw (logic_error) {
	if( timerWasStarted )
	{
		long long beg, end;
		beg = beginTime.tv_sec * 1000000 + beginTime.tv_usec;
		end = duration.tv_sec * 1000000 + duration.tv_usec;
		return double( end - beg ) / 1000000;
	}
}

#endif	//#ifndef TIMER_CPP
