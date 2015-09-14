
#ifndef TIMER_H_
#define TIMER_H_

#include <SDL.h>

#include <cstdint>

class Timer
{


    public:


	Timer();


        /*
         * returns 0 for success
         * returns -1 if timer already started
         */
	int StartTimer();


        /*
         * returns 0 for success
         * returns -1 if timer cannot be restarted
         */
	int RestartTimer();


        /*
         * returns 0 for success
         * returns -1 if timer cannot be stopped
         */
        int StopTimer();


        /*
         * returns the number of ms passed in
         * integer format
         */
	Uint32 GetTimeMs();


        /*
         * returns time passed in a float
         * format.
         */
	float GetTimeSeconds();


        /*
         * returns 0 on success
         * returns -1 if timer can't be paused
         */
        int PauseTimer();


	bool IsStarted();


	bool IsPaused();


	bool IsStopped();


private:


	// Records ticks at start point.
	Uint32 start;


	// Records ticks at stop point.
	Uint32 stop;


	// Records ticks at the pause point.
	Uint32 paused;


	// Tracks whether the timer has started.
	bool is_started;


	// Tracks whether the timer is paused.
	bool is_paused;


	// Tracks whether the timer has stopped.
	bool is_stopped;


};


#endif // TIMER_H_
